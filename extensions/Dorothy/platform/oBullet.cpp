#include "Dorothy/const/oDefine.h"
#include "Dorothy/platform/oPlatformDefine.h"
#include "Dorothy/platform/oBullet.h"
#include "Dorothy/platform/oBulletDef.h"
#include "Dorothy/platform/oUnit.h"
#include "Dorothy/platform/oData.h"
#include "Dorothy/physics/oSensor.h"
#include "Dorothy/physics/oWorld.h"
#include "Dorothy/effect/oEffectCache.h"

NS_DOROTHY_PLATFORM_BEGIN

oBullet::oBullet( oWorld* world, oBulletDef* bulletDef, oUnit* unit ):
oBody(world, bulletDef->getBodyDef()),
type(bulletDef->type),
_bulletDef(bulletDef),
_owner(unit),
_current(0),
_lifeTime(bulletDef->lifeTime),
_face(nullptr)
{
	oBullet::setFaceRight(unit->isFaceRight());
	_detectSensor = oBody::getSensorByTag(oBulletDef::SENSOR_TAG);
	_detectSensor->bodyEnter += std::make_pair(this, &oBullet::onBodyEnter);
	b2Vec2 v = _bulletDef->getVelocity();
	oBody::setVelocity((_isFaceRight ? v.x : -v.x), v.y);
	this->scheduleUpdate();
}

void oBullet::updatePhysics()
{
	if (_bodyB2->IsAwake())
	{
		const b2Vec2& pos = _bodyB2->GetPosition();
		/* Here only CCNode::setPosition(const CCPoint& var) work for modify CCNode`s position.
		 Other positioning functions have been overridden by oBody`s.
		*/
		CCNode::setPosition(CCPoint(oWorld::oVal(pos.x), oWorld::oVal(pos.y)));
		if (_bodyB2->GetGravityScale() != 0.0f)
		{
			b2Vec2 velocity = _bodyB2->GetLinearVelocity();
			CCNode::setRotation(-CC_RADIANS_TO_DEGREES(atan2f(velocity.y, velocity.x)));
		}
	}
}

void oBullet::update( float dt )
{
	_current += dt;
	if (_current >= _lifeTime)
	{
		oBullet::destroy();
	}
}

void oBullet::onExit()
{
	oBody::onExit();
	if (_face)
	{
		CCNode::traverse(
			_face,
			[](CCNode* node)->void
			{
				oIDisposable* item = dynamic_cast<oIDisposable*>(node);
				item->disposing.Clear();
			}
		);
		_face = nullptr;
	}
}

oBullet* oBullet::create( oWorld* world, oBulletDef* def, oUnit* unit )
{
	oBullet* bullet = new oBullet(world, def, unit);
	bullet->autorelease();
	return bullet;
}

oUnit* oBullet::getOwener() const
{
	return _owner;
}

oSensor* oBullet::getDetectSensor() const
{
	return _detectSensor;
}

void oBullet::setFaceRight(bool var)
{
	_isFaceRight = var;
}

bool oBullet::isFaceRight() const
{
	return _isFaceRight;
}

void oBullet::onBodyEnter( oSensor* sensor, oBody* body )
{
	if (body == _owner)
	{
		return;
	}
	bool isHitTerrain = oSharedData.isTerrain(body) && oBullet::targetAllow.isTerrainAllowed();
	bool isHitUnit = oSharedData.isPlayerUnit(body) && oBullet::targetAllow.isAllow(oSharedData.getRelation(_owner, (oUnit*)body));
	bool isRangeDamage = _bulletDef->damageRadius > 0.0f;
	bool isHit = isHitTerrain || isHitUnit;
	if (isHit && hitTarget)
	{
		if (isRangeDamage)
		{
			CCPoint pos = this->getPosition();
			CCRect rect(
				pos.x - _bulletDef->damageRadius,
				pos.y - _bulletDef->damageRadius,
				_bulletDef->damageRadius * 2,
				_bulletDef->damageRadius * 2);
			_world->query(rect, [&](oBody* body)
			{
				if (oSharedData.isPlayerUnit(body) && targetAllow.isAllow(oSharedData.getRelation(_owner, (oUnit*)body)))
				{
					hitTarget(this, (oUnit*)body);
				}
				return false;
			});
		}
		else if (isHitUnit)
		{
			/* hitTarget function may cancel this hit by returning false */
			isHit = hitTarget(this, (oUnit*)body);
		}
	}
	if (isHit)
	{
		oBullet::destroy();
	}
}

oBulletDef* oBullet::getBulletDef()
{
	return _bulletDef;
}

void oBullet::setFace(CCNode* var)
{
	oIDisposable* newItem = dynamic_cast<oIDisposable*>(var);
	if (newItem == nullptr)
	{
		return;
	}
	if (_face)
	{
		oIDisposable* oldItem = dynamic_cast<oIDisposable*>(_face);
		oldItem->disposing.Clear();
		CCNode::removeChild(_face, true);
	}
	_face = var;
	CCNode::addChild(var);
	newItem->disposing = std::make_pair(this, &oBullet::onFaceDisposed);
}

CCNode* oBullet::getFace() const
{
	return _face;
}

void oBullet::onFaceDisposed( oIDisposable* item )
{
	_face = nullptr;
	item->disposing.Clear();
	oBody::destroy();
}

void oBullet::destroy()
{
	CCAssert(_detectSensor != nullptr, "Invoke it once only!");
	_detectSensor->setEnable(false);
	_detectSensor = nullptr;
	CCNode::unscheduleAllSelectors();
	if (_bulletDef->endEffect != oEffectType::None)
	{
		oEffect* effect = oEffect::create(_bulletDef->endEffect);
		effect->setOffset(this->getPosition())
			->attachTo(this->getParent())
			->autoRemove()
			->start();
	}
	oBody::setVelocity(0,0);
	hitTarget.Clear();
	if (_face)
	{
		oIDisposable* item = dynamic_cast<oIDisposable*>(_face);
		item->dispose();
	}
	else
	{
		oBody::destroy();
	}
}

NS_DOROTHY_PLATFORM_END
