#include "Dorothy/const/oDefine.h"
#include "Dorothy/platform/oPlatformDefine.h"
#include "Dorothy/platform/oAI.h"
#include "Dorothy/platform/oUnit.h"
#include "Dorothy/platform/oData.h"
#include "Dorothy/platform/oAction.h"
#include "Dorothy/platform/oAINode.h"
#include "Dorothy/physics/oSensor.h"

NS_DOROTHY_PLATFORM_BEGIN

oExpCompare::oExpCompare( oCompare* left, uint32 op, oCompare* right ):
_left(left),
_and(op==And),
_right(right)
{ }

oExpCompare::~oExpCompare()
{
	CC_SAFE_DELETE(_left);
	CC_SAFE_DELETE(_right);
}

bool oExpCompare::getResult( float leftValue )
{
	return _and ?
		_left->getResult(leftValue) && _right->getResult(leftValue) :
		_left->getResult(leftValue) || _right->getResult(leftValue);
}

bool oValCompare::getResult( float leftValue )
{
	switch (_op)
	{
	case Equal:
		return leftValue == _rightValue;
	case Less:
		return leftValue < _rightValue;
	case LessEqual:
		return leftValue <= _rightValue;
	case Greater:
		return leftValue > _rightValue;
	case GreaterEqual:
		return leftValue >= _rightValue;
	}
	return false;
}

oValCompare::oValCompare( uint32 op, float rightValue ):
_rightValue(rightValue),
_op(op)
{ }

oUnit* oAI::_self = nullptr;

oUnit* oAI::_nearestUnit = nullptr;

oUnit* oAI::_nearestFriend = nullptr;

oUnit* oAI::_nearestEnemy = nullptr;

oUnit* oAI::_nearestNeutral = nullptr;

vector<oUnit*> oAI::_friends;

vector<oUnit*> oAI::_enemies;

vector<oUnit*> oAI::_neutrals;

vector<oUnit*> oAI::_detectedUnits;

float oAI::_lastDeltaInstinctProperty = 0;

oUnit* oAI::self()
{
	return _self;
}

bool oAI::conditionedReflex(oUnit* unit)
{	
	oAILeaf* reflexArc = unit->getReflexArc();
	if (!reflexArc)
	{
		return false;
	}

	_self = unit;

	_nearestUnit = nullptr;
	_nearestFriend = nullptr;
	_nearestEnemy = nullptr;
	_nearestNeutral = nullptr;

	float minUnitDistance = 0;
	float minFriendDistance = 0;
	float minEnemyDistance = 0;
	float minNeutralDistance = 0;

	_friends.clear();
	_enemies.clear();
	_neutrals.clear();
	_detectedUnits.clear();

	oSensor* seneor = unit->getDetectSensor();
	if (seneor)
	{
		for (oBody* body : seneor->getSensedBodies())
		{
			oUnit* aroundUnit = (oUnit*)body;
			_detectedUnits.push_back(aroundUnit);

			float newDistance = ccpDistance(unit->getPosition(), aroundUnit->getPosition());

			if (!_nearestUnit || newDistance < minUnitDistance)
			{
				minUnitDistance = newDistance;
				_nearestUnit = aroundUnit;
			}
			oRelation relation = oSharedData.getRelation(_self, aroundUnit);
			switch (relation)
			{
			case e_friend:
				_friends.push_back(aroundUnit);
				if (!_nearestFriend || newDistance < minFriendDistance)
				{
					minFriendDistance = newDistance;
					_nearestFriend = aroundUnit;
				}
				break;
			case e_enemy:
				_enemies.push_back(aroundUnit);
				if (!_nearestEnemy || newDistance < minEnemyDistance)
				{
					minEnemyDistance = newDistance;
					_nearestEnemy = aroundUnit;
				}
				break;
			case e_neutral:
				_neutrals.push_back(aroundUnit);
				if (!_nearestNeutral || newDistance < minNeutralDistance)
				{
					minNeutralDistance = newDistance;
					_nearestNeutral = aroundUnit;
				}
				break;
			}
		}
	}
	//Do the Conditioned Reflex
	return reflexArc->doAction();
}

bool oAI::condition_UnitCountCompare( oRelation relation, oCompare* compare )
{
	return compare->getResult((float)oAI::getUnitsByRelation(relation).size());
}

bool oAI::condition_UnitTypeCountCompare(oRelation relation, uint32 type, oCompare* compare)
{
	uint32 count = 0;
	for (oUnit* unit : oAI::getUnitsByRelation(relation))
	{
		if (unit->getUnitDef()->type == type)
		{
			count++;
		}
	}
	return compare->getResult((float)count);
}

bool oAI::condition_UnitDistanceCompareCountCompare(oRelation relation, oCompare* compareDistance, oCompare* compareCount)
{
	uint32 count = 0;
	for (oUnit* unit : oAI::getUnitsByRelation(relation))
	{
		float distance = ccpDistance(_self->getPosition(), unit->getPosition());
		if (compareDistance->getResult(distance))
		{
			count++;
		}
	}
	return compareCount->getResult((float)count);
}

bool oAI::condition_UnitHpCompareCountCompare(oRelation relation, oCompare* compareHp, oCompare* compareCount)
{
	uint32 count = 0;
	for (oUnit* unit : oAI::getUnitsByRelation(relation))
	{
		if (compareHp->getResult(unit->properties["hp"]))
		{
			count++;
		}
	}
	return compareCount->getResult((float)count);
}

bool oAI::condition_UnitHpPercentCompareCountCompare(oRelation relation, oCompare* comparePercent, oCompare* compareCount)
{
	uint32 count = 0;
	for (oUnit* unit : oAI::getUnitsByRelation(relation))
	{
		float hpPercent = unit->properties["hp"] / unit->maxHp;
		if (comparePercent->getResult(hpPercent))
		{
			count++;
		}
	}
	return compareCount->getResult((float)count);
}

bool oAI::condition_UnitPropertyCompareCountCompare( oRelation relation, const string& name, oCompare* compareProperty, oCompare* compareCount )
{
	uint32 count = 0;
	for (oUnit* unit : oAI::getUnitsByRelation(relation))
	{
		oProperty* prop = unit->properties.get(name);
		if (prop && compareProperty->getResult(*prop))
		{
			count++;
		}
	}
	return compareCount->getResult((float)count);
}

bool oAI::condition_AnyUnitDoingAction( oRelation relation, uint32 actionId )
{
	for (oUnit* unit : oAI::getUnitsByRelation(relation))
	{
		oAction* action = unit->getCurrentAction();
		if (action && action->getId() == actionId)
		{
			return true;
		}
	}
	return false;
}

bool oAI::condition_AnyUnitDistanceCompare( oRelation relation, oCompare* compare )
{
	for (oUnit* unit : oAI::getUnitsByRelation(relation))
	{
		float newDistance = ccpDistance(_self->getPosition(), unit->getPosition());
		if (compare->getResult(newDistance))
		{
			return true;
		}
	}
	return false;
}

bool oAI::condition_AnyUnitHpCompare( oRelation relation, oCompare* compare )
{
	for (oUnit* unit : oAI::getUnitsByRelation(relation))
	{
		if (compare->getResult(unit->properties["hp"]))
		{
			return true;
		}
	}
	return false;
}

bool oAI::condition_AnyUnitHpPercentCompare( oRelation relation, oCompare* compare )
{
	for (oUnit* unit : oAI::getUnitsByRelation(relation))
	{
		if (compare->getResult(unit->properties["hp"] / unit->maxHp))
		{
			return true;
		}
	}
	return false;
}

bool oAI::condition_AnyUnitPropertyCompare( oRelation relation, const string& name, oCompare* compare )
{
	for (oUnit* unit : oAI::getUnitsByRelation(relation))
	{
		oProperty* prop = unit->properties.get(name);
		if (prop && compare->getResult(*prop))
		{
			return true;
		}
	}
	return false;
}

bool oAI::condition_NearestUnitDoingAction( oRelation relation, uint32 actionId )
{
	oUnit* unit = oAI::getNearestUnitByRelation(relation);
	if (unit)
	{
		oAction* action = unit->getCurrentAction();
		return action && action->getId() == actionId;
	}
	return false;
}

bool oAI::condition_NearestUnitHpCompare( oRelation relation, oCompare* compare )
{
	oUnit* unit = oAI::getNearestUnitByRelation(relation);
	if (unit)
	{
		return compare->getResult(unit->properties["hp"]);
	}
	return false;
}

bool oAI::condition_NearestUnitHpPercentCompare( oRelation relation, oCompare* compare )
{
	oUnit* unit = oAI::getNearestUnitByRelation(relation);
	if (unit)
	{
		return compare->getResult(unit->properties["hp"] / unit->maxHp);
	}
	return false;
}

bool oAI::condition_NearestUnitPropertyCompare( oRelation relation, const string& name, oCompare* compare )
{
	oUnit* unit = oAI::getNearestUnitByRelation(relation);
	if (unit)
	{
		oProperty* prop = unit->properties.get(name);
		return prop && compare->getResult(*prop);
	}
	return false;
}

bool oAI::condition_SelfHpCompare( oCompare* compare )
{
	return compare->getResult(_self->properties["hp"]);
}

bool oAI::condition_SelfHpPercentCompare( oCompare* compare )
{
	return compare->getResult(_self->properties["hp"] / _self->maxHp);
}

bool oAI::condition_SelfPropertyCompare( const string& name, oCompare* compare )
{
	oProperty* prop = _self->properties.get(name);
	return prop && compare->getResult(*prop);
}

bool oAI::condition_UnitWithTagDoingAction( int tag, uint32 actionId )
{
	oUnit* unit = oAI::getUnitByTag(tag);
	if (unit)
	{
		oAction* action = unit->getCurrentAction();
		return action && action->getId() == actionId;
	}
	return false;
}

bool oAI::condition_UnitWithTagDistanceCompare( int tag, oCompare* compare )
{
	oUnit* unit = oAI::getUnitByTag(tag);
	if (unit)
	{
		float distance = ccpDistance(_self->getPosition(), unit->getPosition());
		return compare->getResult(distance);
	}
	return false;
}

bool oAI::condition_UnitWithTagHpCompare( int tag, oCompare* compare )
{
	oUnit* unit = oAI::getUnitByTag(tag);
	if (unit)
	{
		return compare->getResult(unit->properties["hp"]);
	}
	return false;
}

bool oAI::condition_UnitWithTagHpPercentCompare( int tag, oCompare* compare )
{
	oUnit* unit = oAI::getUnitByTag(tag);
	if (unit)
	{
		float hpPercent = unit->properties["hp"] / unit->maxHp;
		return compare->getResult(hpPercent);
	}
	return false;
}

bool oAI::condition_UnitWithTagPropertyCompare( int tag, const string& name, oCompare* compare )
{
	oUnit* unit = oAI::getUnitByTag(tag);
	if (unit)
	{
		oProperty* prop = unit->properties.get(name);
		return prop && compare->getResult(*prop);
	}
	return false;
}

bool oAI::condition_SelfFaceLeft()
{
	return !_self->isFaceRight();
}

bool oAI::condition_NearestUnitFaceLeft( oRelation relation )
{
	oUnit* unit = oAI::getNearestUnitByRelation(relation);
	if (unit)
	{
		return !unit->isFaceRight();
	}
	return false;
}

bool oAI::condition_UnitWithTagFaceLeft( int tag )
{
	oUnit* unit = oAI::getUnitByTag(tag);
	if (unit)
	{
		return !unit->isFaceRight();
	}
	return false;
}

bool oAI::condition_NearestUnitAtUnitLeft( oRelation relation )
{
	oUnit* unit = oAI::getNearestUnitByRelation(relation);
	if (unit)
	{
		return unit->getPositionX() < _self->getPositionX();
	}
	return false;
}

bool oAI::condition_UnitWithTagAtUnitLeft( int tag )
{
	oUnit* unit = oAI::getUnitByTag(tag);
	if (unit)
	{
		return unit->getPositionX() < _self->getPositionX();
	}
	return false;
}

bool oAI::condition_LastChangedInstinctPropertyDeltaCompare( oCompare* compare )
{
	return compare->getResult(_lastDeltaInstinctProperty);
}

const vector<oUnit*>& oAI::getUnitsByRelation( oRelation relation )
{
	vector<oUnit*>& units = _detectedUnits;
	switch (relation)
	{
	case e_friend:
		units = _friends;
		break;
	case e_enemy:
		units = _enemies;
		break;
	case e_neutral:
		units = _neutrals;
		break;
	}
	return units;
}

oUnit* oAI::getNearestUnitByRelation( oRelation relation )
{
	switch (relation)
	{
	case e_friend:
		return _nearestFriend;
	case e_enemy:
		return _nearestEnemy;
	case e_neutral:
		return _nearestNeutral;
	}
	return _nearestUnit;
}

oUnit* oAI::getUnitByTag( int tag )
{
	for (oUnit* unit : _detectedUnits)
	{
		if (unit->getTag() == tag)
		{
			return unit;
		}
	}
	return nullptr;
}

float oAI::getLastDeltaInstinctProperty()
{
	return _lastDeltaInstinctProperty;
}

NS_DOROTHY_PLATFORM_END
