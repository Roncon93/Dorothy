#include "Dorothy/const/oDefine.h"
#include "Dorothy/platform/oPlatformDefine.h"
#include "Dorothy/platform/oUnit.h"
#include "Dorothy/platform/oAction.h"
#include "Dorothy/platform/oData.h"
#include "Dorothy/platform/oBulletDef.h"
#include "Dorothy/platform/oAINode.h"
#include "Dorothy/platform/oAI.h"
#include "Dorothy/platform/oPlatformWorld.h"

#include "Dorothy/model/oModelDef.h"
#include "Dorothy/model/oModel.h"
#include "Dorothy/physics/oSensor.h"
#include "Dorothy/platform/oProperty.h"

NS_DOROTHY_PLATFORM_BEGIN

oUnit::oUnit(oWorld* world, oUnitDef* unitDef):
oBody(world, unitDef->getBodyDef()),
_model(nullptr),
_detectSensor(nullptr),
_attackSensor(nullptr),
_isFaceRight(true),
_currentAction(nullptr),
_size(unitDef->getSize()),
move(unitDef->move),
moveSpeed(1.0f),
jump(unitDef->jump),
attackSpeed(1.0f),
maxHp(unitDef->maxHp),
attackBase(unitDef->attackBase),
attackBonus(0),
attackFactor(1.0f),
attackType(unitDef->attackType),
attackTarget(unitDef->attackTarget),
attackPower(unitDef->attackPower),
targetAllow(unitDef->targetAllow),
damageType(unitDef->damageType),
defenceType(unitDef->defenceType),
sensity(unitDef->sensity),
_bulletDef(unitDef->getBulletDef()),
_unitDef(unitDef)
{
	properties.setOwner(this);
	properties["hp"] = unitDef->maxHp;
	instincts.setOwner(this);
	oUnit::setDetectDistance(unitDef->detectDistance);
	oUnit::setAttackRange(unitDef->attackRange);
	_groundSensor = oBody::getSensorByTag(oUnitDef::GroundSensorTag);
	this->scheduleUpdate();
}

oUnitDef* oUnit::getUnitDef() const
{
	return _unitDef;
}

void oUnit::setFaceRight( bool var )
{
	if (_isFaceRight != var)
	{
		_isFaceRight = var;
		if (_model)
		{
			_model->setFaceRight(var);
		}
	}
}

bool oUnit::isFaceRight() const
{
	return _isFaceRight;
}

void oUnit::setModel( oModel* model )
{
	if (_model != model)
	{
		if (_model != nullptr)
		{
			this->removeChild(_model, true);
		}
		if (model)
		{
			this->addChild(model);
			model->setFaceRight(_isFaceRight);
		}
		_model = model;
	}
}

oModel* oUnit::getModel() const
{
	return _model;
}

oUnit* oUnit::create(oWorld* world, oUnitDef* unitDef)
{
	oUnit* unit = new oUnit(world, unitDef);
	unit->autorelease();
	return unit;
}

void oUnit::update( float dt )
{
	if (_currentAction != nullptr)
	{
		_currentAction->update(dt);
		if (_currentAction && !_currentAction->isDoing())
		{
			_currentAction = nullptr;
		}
	}
	else
	{
		oAI::conditionedReflex(this);
	}
}

void oUnit::setGroup( int group )
{
	_group = group;
	for (b2Fixture* f = _bodyB2->GetFixtureList();f;f = f->GetNext())
	{
		if (f->IsSensor())
		{
			oSensor* sensor = (oSensor*)f->GetUserData();
			if (sensor->getTag() != oUnitDef::GroundSensorTag)
			{
				continue;
			}
		}
		f->SetFilterData(oBody::getWorld()->getFilter(group));
	}
}

float oUnit::getWidth() const
{
	return _size.width;
}

float oUnit::getHeight() const
{
	return _size.height;
}

oAction* oUnit::attachAction( int id )
{
	auto it = _actions.find(id);
	if (it == _actions.end())
	{
		oAction* action = oAction::create(id, this);
		if (action)
		{
			_actions[id] = oOwnMake(action);
		}
		return action;
	}
	return it->second;
}

void oUnit::attachAction( oAction* action )
{
	_actions[action->getId()] = oOwnMake(action);
}

oAction* oUnit::getAction( int id ) const
{
	oActionMap::const_iterator it = _actions.find(id);
	return it == _actions.end() ? nullptr : it->second.get();
}

bool oUnit::doIt( int id )
{
	oActionMap::iterator it = _actions.find(id);
	if (it != _actions.end())
	{
		oAction* action = it->second;
		if (!action->isDoing() && action->isAvailable())
		{
			if (_currentAction != nullptr && _currentAction->isDoing())
			{
				if (_currentAction->getPriority() < action->getPriority())
				{
					_currentAction->stop();
					_currentAction = nullptr;
				}
				else
				{
					return false;
				}
			}
			action->run();
			if (action->isDoing())
			{
				_currentAction = action;
			}
			return true;
		}
	}
	return false;
}

bool oUnit::isOnSurface() const
{
	return _groundSensor && !_groundSensor->getSensedBodies().empty();
}

void oUnit::setDetectDistance(float var)
{
	_detectDistance = var;
	if (_detectSensor)
	{
		oBody::removeSensor(_detectSensor);
		_detectSensor = nullptr;
	}
	if (var > 0)
	{
		_detectSensor = oBody::attachSensor(oUnitDef::DetectSensorTag, oBodyDef::circle(var));
		_detectSensor->setGroup(oSharedData.getSensePlayerGroup());
	}
}

void oUnit::setAttackRange(const CCSize& var)
{
	_attackRange = var;
	if (_attackSensor)
	{
		oBody::removeSensor(_attackSensor);
		_attackSensor = nullptr;
	}
	if (var.width != 0.0f && var.height != 0.0f)
	{
		_attackSensor = oBody::attachSensor(oUnitDef::AttackSensorTag, oBodyDef::polygon(var.width*2, var.height));
		_attackSensor->setGroup(oSharedData.getSensePlayerGroup());
	}
}

const CCSize& oUnit::getAttackRange() const
{
	return _attackRange;
}

float oUnit::getDetectDistance() const
{
	return _detectDistance;
}

oSensor* oUnit::getGroundSensor() const
{
	return _groundSensor;
}

oSensor* oUnit::getDetectSensor() const
{
	return _detectSensor;
}

oSensor* oUnit::getAttackSensor() const
{
	return _attackSensor;
}

void oUnit::setBulletDef(oBulletDef* var)
{
	_bulletDef = var;
}

oBulletDef* oUnit::getBulletDef() const
{
	return _bulletDef;
}

oAction* oUnit::getCurrentAction() const
{
	return _currentAction;
}

oUnit::oPropertySet::~oPropertySet()
{
	for (auto it : _items) delete it.second;
}
void oUnit::oPropertySet::setOwner( oUnit* owner )
{
	_owner = owner;
	_items["hp"] = new oProperty(_owner);//Add the default property "hp"
}
oProperty& oUnit::oPropertySet::operator[]( const string& name )
{
	auto it = _items.find(name);
	if (it != _items.end())
	{
		return *it->second;
	}
	else
	{
		oProperty* prop = new oProperty(_owner);
		_items[name] = prop;
		_owner->instincts.reinstall();
		return *prop;
	}
}
const oProperty& oUnit::oPropertySet::operator[]( const string& name ) const
{
	return *_items[name];
}
void oUnit::oPropertySet::remove( const string& name )
{
	if (name != "hp")
	{
		auto it = _items.find(name);
		if (it != _items.end())
		{
			_items.erase(it);
		}
	}
}
void oUnit::oPropertySet::clear()
{
	float temp = *_items["hp"];
	_items.clear();
	for (auto it : _items) delete it.second;
	_items["hp"] = new oProperty(_owner, temp);//Add the default property "hp"
}
oProperty* oUnit::oPropertySet::get( const string& name ) const
{
	auto it = _items.find(name);
	return it == _items.end() ? nullptr : it->second;
}

void oUnit::oInstinctSet::add( oInstinct* instinct )
{
	_instincts.push_back(instinct);
	instinct->install(_owner);
}

void oUnit::oInstinctSet::remove( oInstinct* instinct )
{
	oRef<oInstinct> temp(instinct);
	if (_instincts.remove(instinct))
	{
		instinct->uninstall(_owner);
	}
}

void oUnit::oInstinctSet::clear()
{
	for (oInstinct* instinct : _instincts)
	{
		instinct->uninstall(_owner);
	}
	_instincts.clear();
}

void oUnit::oInstinctSet::setOwner( oUnit* owner )
{
	_owner = owner;
}

void oUnit::oInstinctSet::reinstall()
{
	for (oInstinct* instinct : _instincts)
	{
		instinct->install(_owner);
	}
}

void oUnit::setReflexArc(oAILeaf* var)
{
	if (var)
	{
		_reflexArc = var;
		oAI::conditionedReflex(this);
	}
}

oAILeaf* oUnit::getReflexArc() const
{
	return _reflexArc;
}

NS_DOROTHY_PLATFORM_END
