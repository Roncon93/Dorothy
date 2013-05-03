#include "Dorothy/const/oDefine.h"
#include "Dorothy/platform/oPlatformDefine.h"
#include "Dorothy/platform/oBulletDef.h"
#include "Dorothy/platform/oBullet.h"
#include "Dorothy/platform/oUnit.h"
#include "Dorothy/platform/oData.h"
#include "Dorothy/physics/oBodyDef.h"
#include "Dorothy/model/oClip.h"
#include "Dorothy/model/oModelDef.h"
#include "Dorothy/model/oModel.h"
#include "Dorothy/model/oFace.h"
#include "Dorothy/effect/oEffectCache.h"

NS_DOROTHY_PLATFORM_BEGIN

const int oBulletDef::SENSOR_TAG = 0;

oBulletDef::oBulletDef():
type(0),
lifeTime(0),
damageRadius(0),
endEffect(oEffectType::None),
_bodyDef(oBodyDef::create())
{ }

oBodyDef* oBulletDef::getBodyDef() const
{
	return _bodyDef;
}

oBulletDef* oBulletDef::create()
{
	oBulletDef* def = new oBulletDef();
	def->autorelease();
	return def;
}

oBullet* oBulletDef::toBullet( oWorld* world, oUnit* unit )
{
	oBullet* bullet = oBullet::create(world, this, unit);
	bullet->setGroup(oSharedData.getSenseAllGroup());
	if (_face)
	{
		CCNode* node = _face->toNode();
		bullet->setFace(node);
	}
	oModel* model = unit->getModel();
	const CCPoint& offset = (model ? model->getModelDef()->getKeyPoint(oUnitDef::BulletKey) : CCPointZero);
	bullet->setPosition(
		ccpAdd(
			unit->getPosition(),
			(unit->isFaceRight() ? ccp(-offset.x, offset.y) : offset)));
	if (_bodyDef->gravityScale != 0.0f)
	{
		bullet->setRotation(-CC_RADIANS_TO_DEGREES(atan2f(_velocity.y, unit->isFaceRight() ? _velocity.x : -_velocity.x)));
	}
	return bullet;
}

void oBulletDef::setVelocity( float angle, float speed )
{
	angle = CC_DEGREES_TO_RADIANS(angle);
	_velocity.Set(cosf(angle) * speed, sinf(angle) * speed);
}

void oBulletDef::setVelocity( const b2Vec2& velocity )
{
	_velocity = velocity;
}

const b2Vec2& oBulletDef::getVelocity() const
{
	return _velocity;
}

void oBulletDef::setIsHighSpeed(bool var)
{
	_bodyDef->bullet = var;
}

bool oBulletDef::getIsHighSpeed() const
{
	return _bodyDef->bullet;
}

void oBulletDef::setGravityScale(float var)
{
	_bodyDef->gravityScale = var;
}

float oBulletDef::getGravityScale() const
{
	return _bodyDef->gravityScale;
}

void oBulletDef::setAsCircle( float radius )
{
	_bodyDef->clearFixtures();
	_bodyDef->attachCircleSensor(SENSOR_TAG, radius);
}

void oBulletDef::setFace(oFace* var)
{
	_face = var;
}

oFace* oBulletDef::getFace() const
{
	return _face;
}

NS_DOROTHY_PLATFORM_END
