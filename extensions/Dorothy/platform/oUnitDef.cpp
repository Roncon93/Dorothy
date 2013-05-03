#include "Dorothy/const/oDefine.h"
#include "Dorothy/platform/oPlatformDefine.h"
#include "Dorothy/platform/oUnitDef.h"
#include "Dorothy/platform/oUnit.h"
#include "Dorothy/platform/oBulletDef.h"

#include "Dorothy/model/oModelDef.h"
#include "Dorothy/model/oModelCache.h"
#include "Dorothy/physics/oBodyDef.h"
#include "Dorothy/physics/oWorld.h"
#include "Dorothy/effect/oEffectCache.h"
#include "Dorothy/physics/oSensor.h"

NS_DOROTHY_PLATFORM_BEGIN

const float oUnitDef::BOTTOM_OFFSET(4.0f);
const float oUnitDef::GROUND_SENSOR_HEIGHT(4.0f);

oUnitDef::oUnitDef():
type(0),
sensity(0),
move(0),
jump(0),
maxHp(0),
detectDistance(0),
attackBase(0),
attackDelay(0),
attackEffect(oEffectType::None),
attackEffectDelay(0),
attackRange(),
attackPower(),
attackType(e_attackMelee),
attackTarget(e_targetOne),
damageType(e_damageOne),
defenceType(e_defenceOne),
hitEffect(oEffectType::None),
bulletType(-1)
{ }

oUnitDef* oUnitDef::create( const string& modelFile, const CCSize& size, float density, float friction, float restitution )
{
	oUnitDef* unitDef = new oUnitDef();
	unitDef->autorelease();

	if (modelFile.size() > 0)
	{
		unitDef->_modelDef = oSharedModelCache.load(modelFile.c_str());
		unitDef->_modelDef->retain();
	}
	unitDef->_size = size;
	oBodyDef* bodyDef = oBodyDef::create();
	if (!size.equals(CCSizeZero))
	{
		bodyDef->fixedRotation = true;
		float hw = size.width * 0.5f;
		float hh = size.height * 0.5f;
		vector<b2Vec2> vertices(4);
		vertices[0].Set(-hw, hh);
		vertices[1].Set(-hw + BOTTOM_OFFSET, -hh);
		vertices[2].Set(hw - BOTTOM_OFFSET, -hh);
		vertices[3].Set(hw, hh);
		bodyDef->attachPolygon(vertices, density, friction, restitution);
		bodyDef->attachPolygonSensor(
			oUnitDef::GroundSensorTag,
			size.width - BOTTOM_OFFSET * 2,
			GROUND_SENSOR_HEIGHT,
			b2Vec2(0, -hh - GROUND_SENSOR_HEIGHT * 0.5f),
			0);
	}
	unitDef->_bodyDef = bodyDef;
	return unitDef;
}

oUnit* oUnitDef::toUnit( oWorld* world, int group, float x, float y, bool isFaceRight )
{
	oUnit* unit = oUnit::create(world, this);
	unit->setGroup(group);
	unit->setPosition(x, y);
	unit->setRotation(-CC_RADIANS_TO_DEGREES(_bodyDef->angle));
	oModel* model = _modelDef ? _modelDef->toModel() : oModel::none();
	unit->setModel(model);
	unit->setFaceRight(isFaceRight);
	for (int id : actions)
	{
		unit->attachAction(id);
	}
	return unit;
}

oBodyDef* oUnitDef::getBodyDef() const
{
	return _bodyDef;
}

oModelDef* oUnitDef::getModelDef() const
{
	return _modelDef;
}

const CCSize& oUnitDef::getSize() const
{
	return _size;
}

void oUnitDef::setBulletDef(oBulletDef* var)
{
	_bulletDef = var;
}

oBulletDef* oUnitDef::getBulletDef() const
{
	return _bulletDef;
}

void oUnitDef::setIsStatic(bool var)
{
	_bodyDef->type = var ? b2_staticBody : b2_dynamicBody;
}

bool oUnitDef::getIsStatic() const
{
	return _bodyDef->type == b2_staticBody;
}

NS_DOROTHY_PLATFORM_END
