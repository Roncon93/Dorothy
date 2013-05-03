#include "Dorothy/const/oDefine.h"
#include "Dorothy/platform/oPlatformDefine.h"
#include "Dorothy/platform/oAction.h"
#include "Dorothy/platform/oUnit.h"
#include "Dorothy/platform/oData.h"
#include "Dorothy/platform/oBulletDef.h"
#include "Dorothy/platform/oBullet.h"
#include "Dorothy/platform/oAI.h"
#include "Dorothy/model/oModelDef.h"
#include "Dorothy/model/oModel.h"
#include "Dorothy/physics/oSensor.h"
#include "Dorothy/physics/oWorld.h"
#include "Dorothy/effect/oEffectCache.h"

NS_DOROTHY_PLATFORM_BEGIN

// oAction
oAction::oAction(int id, int priority, oUnit* owner):
_id(id),
_priority(priority),
_isDoing(false),
_owner(owner),
reaction(0.0f)
{ }

oAction::~oAction()
{
	_owner = nullptr;
}

int oAction::getId() const
{
	return _id;
}

int oAction::getPriority() const
{
	return _priority;
}

bool oAction::isDoing() const
{
	return _isDoing;
}

oUnit* oAction::getOwner() const
{
	return _owner;
}

bool oAction::isAvailable()
{
	return true;
}

void oAction::run()
{
	_isDoing = true;
	_reflexDelta = 0.0f;
}

void oAction::update( float dt )
{
	_reflexDelta += dt;
	if (_reflexDelta >= _owner->sensity + oAction::reaction)
	{
		_reflexDelta = 0.0f;
		//Check AI here
		oAI::conditionedReflex(_owner);
	}
}

void oAction::stop()
{
	_isDoing = false;
}

oAction* oAction::create( int id, oUnit* unit )
{
	return oActionHelper::create(id, unit);
}

// oWalk
oWalk::oWalk( oUnit* unit ):
oAction(oID::ActionWalk, oID::PriorityWalk, unit)
{
	oAction::reaction = oID::ReactionWalk;
}

bool oWalk::isAvailable()
{
	return _owner->isOnSurface();
}

void oWalk::run()
{
	oAction::run();
	oModel* model = _owner->getModel();
	model->setSpeed(_owner->moveSpeed);
	model->setLoop(true);
	model->setLook(oID::LookHappy);
	model->setRecovery(0.1f);
	model->play(oID::AnimationWalk);
	float move = _owner->move * _owner->moveSpeed;
	_owner->setVelocityX(_owner->isFaceRight() ? move : -move);
	if (actionStart)
	{
		actionStart(this);
	}
}

void oWalk::update(float dt)
{
	if (_owner->isOnSurface())
	{
		float move = _owner->move * _owner->moveSpeed;
		_owner->setVelocityX(_owner->isFaceRight() ? move : -move);
	}
	else
	{
		oWalk::stop();
		if (actionEnd)
		{
			actionEnd(this);
		}
	}
	oAction::update(dt);
}

void oWalk::stop()
{
	oAction::stop();
	_owner->getModel()->stop();
}

oAction* oWalk::create(oUnit* unit)
{
	return new oWalk(unit);
}

// oTurn
oTurn::oTurn( oUnit* unit ):
oAction(oID::ActionTurn, oID::PriorityTurn, unit)
{ }

void oTurn::run()
{
	_owner->setFaceRight(!_owner->isFaceRight());
	if (actionStart)
	{
		actionStart(this);
	}
	if (actionEnd)
	{
		actionEnd(this);
	}
}

oAction* oTurn::create( oUnit* unit )
{
	return new oTurn(unit);
}

oIdle::oIdle( oUnit* unit ):
oAction(oID::ActionIdle, oID::PriorityIdle, unit)
{
	oAction::reaction = oID::ReactionIdle;
}

void oIdle::run()
{
	oAction::run();
	oModel* model = _owner->getModel();
	model->setSpeed(1.0f);
	model->setLoop(true);
	model->setLook(oID::LookHappy);
	model->setRecovery(0.05f);
	if (!_owner->isOnSurface())
	{
		oModel* model = _owner->getModel();
		model->resume(oID::AnimationJump);
	}
	else
	{
		model->resume(oID::AnimationIdle);
	}
	if (actionStart)
	{
		actionStart(this);
	}
}

void oIdle::update(float dt)
{
	if (!_owner->isOnSurface())
	{
		oModel* model = _owner->getModel();
		model->resume(oID::AnimationJump);
	}
	oAction::update(dt);
}

void oIdle::stop()
{
	oAction::stop();
	_owner->getModel()->stop();
	if (actionEnd)
	{
		actionEnd(this);
	}
}

oAction* oIdle::create( oUnit* unit )
{
	return new oIdle(unit);
}

oJump::oJump( oUnit* unit ):
oAction(oID::ActionJump, oID::PriorityJump, unit)
{
	oAction::reaction = oID::ReactionJump;
}

bool oJump::isAvailable()
{
	return _owner->isOnSurface();
}

void oJump::run()
{
	oAction::run();
	oModel* model = _owner->getModel();
	model->setSpeed(1.0f);
	model->setLoop(true);
	model->setLook(oID::LookHappy);
	model->setRecovery(0.1f);
	model->resume(oID::AnimationJump);
	_current = 0.0f;
	_owner->setVelocityY(_owner->jump);
	oSensor* sensor = _owner->getGroundSensor();
	b2Body* self = _owner->getB2Body();
	b2Body* target = sensor->getSensedBodies()[0]->getB2Body();
	b2DistanceInput input =
	{
		b2DistanceProxy(self->GetFixtureList()->GetShape(), 0),
		b2DistanceProxy(target->GetFixtureList()->GetShape(), 0),
		self->GetTransform(),
		target->GetTransform()
	};
	b2DistanceOutput output;
	b2Distance(&output, &input);
	target->ApplyLinearImpulse(
		b2Vec2(-self->GetMass() * self->GetLinearVelocityX(),
			-self->GetMass() * self->GetLinearVelocityY()),
		output.pointB);
	if (actionStart)
	{
		actionStart(this);
	}
}

void oJump::update(float dt)
{
	if (_current < 0.2f)//don`t check for ground for a while, for actor won`t lift immediately.
	{
		_current += dt;
		oJump::stop();
		if (actionEnd)
		{
			actionEnd(this);
		}
	}
	oAction::update(dt);
}

void oJump::stop()
{
	oAction::stop();
	_owner->getModel()->pause();
}

oAction* oJump::create( oUnit* unit )
{
	return new oJump(unit);
}

oStop::oStop( oUnit* unit ):
oAction(oID::ActionStop, oID::PriorityStop, unit)
{ }

void oStop::run()
{ }

oAction* oStop::create( oUnit* unit )
{
	return new oStop(unit);
}

// oAttack
bool oAttack::usePreciseHit = true;

oAttack::oAttack(int id, oUnit* unit ):
oAction(id, oID::PriorityAttack, unit)
{
	oModel* model = unit->getModel();
	model->handlers[oID::AnimationAttack] += std::make_pair(this, &oMeleeAttack::onAnimationEnd);
}

oAttack::~oAttack()
{
	oModel* model = _owner->getModel();
	model->handlers[oID::AnimationAttack] -= std::make_pair(this, &oMeleeAttack::onAnimationEnd);
}

void oAttack::run()
{
	oAction::run();
	_current = 0;
	_attackDelay = _owner->getUnitDef()->attackDelay / _owner->attackSpeed;
	_attackEffectDelay = _owner->getUnitDef()->attackEffectDelay / _owner->attackSpeed;
	oModel* model = _owner->getModel();
	model->setLoop(false);
	model->setLook(oID::LookFight);
	model->setRecovery(0.0f);
	model->setSpeed(_owner->attackSpeed);
	model->play(oID::AnimationAttack);
	if (actionStart)
	{
		actionStart(this);
	}
}

void oAttack::update( float dt )
{
	_current += dt;
	if (_attackDelay >= 0 && _current >= _attackDelay)
	{
		_attackDelay = -1;
		this->onAttack();
	}
	if (_attackEffectDelay >= 0 && _current >= _attackEffectDelay)
	{
		_attackEffectDelay = -1;
		int attackEffect = _owner->getUnitDef()->attackEffect;
		if (attackEffect != oEffectType::None)
		{
			CCPoint key = _owner->getModel()->getModelDef()->getKeyPoint(oUnitDef::AttackKey);
			if (_owner->getModel()->getModelDef()->isFaceRight() != _owner->isFaceRight())
			{
				key.x = -key.x;
			}
			oEffect* effect = oEffect::create(attackEffect);
			effect->setOffset(key)->attachTo(_owner)->autoRemove()->start();
		}
	}
}

void oAttack::stop()
{
	oAction::stop();
	_owner->getModel()->stop();
}

void oAttack::onAnimationEnd( oModel* model )
{
	if (oAction::isDoing())
	{
		this->stop();
		if (actionEnd)
		{
			actionEnd(this);
		}
	}
}

float oAttack::getDamage( oUnit* target )
{
	float factor = oSharedData.getDamageFactor(_owner->damageType, target->defenceType);
	float damage = (_owner->attackBase + _owner->attackBonus) * (_owner->attackFactor + factor);
	return damage;
}

CCPoint oAttack::getHitPoint( oBody* self, oBody* target, b2Shape* selfShape )
{
	CCPoint hitPoint;
	float distance = -1;
	for (b2Fixture* f = target->getB2Body()->GetFixtureList();f;f = f->GetNext())
	{
		if (!f->IsSensor())
		{
			b2DistanceInput input =
			{
				b2DistanceProxy(selfShape, 0),
				b2DistanceProxy(f->GetShape(), 0),
				self->getB2Body()->GetTransform(),
				target->getB2Body()->GetTransform()
			};
			b2DistanceOutput output;
			b2Distance(&output, &input);
			if (distance == -1 || distance > output.distance)
			{
				distance = output.distance;
				hitPoint = ccp(oWorld::oVal(output.pointB.x), oWorld::oVal(output.pointB.y));
			}
		}
	}
	return hitPoint;
}

// oMeleeAttack
oMeleeAttack::oMeleeAttack( oUnit* unit ):
oAttack(oID::ActionMeleeAttack, unit)
{
	_polygon.SetAsBox(oWorld::b2Val(_owner->getWidth()*0.5f), 0.0005f);
}

void oMeleeAttack::onAttack()
{
	oSensor* sensor = _owner->getAttackSensor();
	if (sensor)
	{
		for (oBody* body : sensor->getSensedBodies())
		{
			oUnit* target = (oUnit*)body;
			BLOCK_START
			{
				bool attackRight = _owner->getPositionX() < target->getPositionX();
				bool faceRight = _owner->isFaceRight();
				BREAK_IF(attackRight != faceRight);//!(hitRight == faceRight || hitLeft == faceLeft)
				oRelation relation = oSharedData.getRelation(_owner, target);
				BREAK_IF(!_owner->targetAllow.isAllow(relation));
				/* Get hit point */
				oHit* hitAction = (oHit*)(target->getAction(oID::ActionHit));
				if (hitAction)
				{
					CCPoint hitPoint = oAttack::usePreciseHit ? oAttack::getHitPoint(_owner, target, &_polygon) : target->getPosition();
					hitAction->setHitInfo(hitPoint, _owner->attackPower, !attackRight);
				}
				/* Make damage */
				float damage = oAttack::getDamage(target);
				target->properties["hp"] -= damage;
				if (damaged)
				{
					damaged(_owner, target, damage);
				}
			}
			BLOCK_END
		}
		//SimpleAudioEngine::sharedEngine()->playEffect("sound/f_att.wav");
	}
}

oAction* oMeleeAttack::create( oUnit* unit )
{
	return new oMeleeAttack(unit);
}

// oRangeAttack
oRangeAttack::oRangeAttack( oUnit* unit ):
oAttack(oID::ActionRangeAttack, unit)
{ }

oAction* oRangeAttack::create( oUnit* unit )
{
	return new oRangeAttack(unit);
}

void oRangeAttack::onAttack()
{
	oBulletDef* bulletDef = _owner->getBulletDef();
	if (bulletDef)
	{
		oBullet* bullet = bulletDef->toBullet(_owner->getWorld(), _owner);
		bullet->targetAllow = _owner->targetAllow;
		bullet->hitTarget = std::make_pair(this, &oRangeAttack::onHitTarget);
		_owner->getWorld()->addChild(bullet, _owner->getZOrder());
		//SimpleAudioEngine::sharedEngine()->playEffect("sound/d_att.wav");
	}
}

bool oRangeAttack::onHitTarget( oBullet* bullet, oUnit* target )
{
	/* Get hit point */
	oHit* hitAction = (oHit*)(target->getAction(oID::ActionHit));
	if (hitAction)
	{
		b2Shape* shape = bullet->getDetectSensor()->getFixture()->GetShape();
		CCPoint hitPoint = oAttack::usePreciseHit ? oAttack::getHitPoint(_owner, target, shape) : target->getPosition();
		bool attackRight = bullet->getVelocityX() > 0.0f;
		hitAction->setHitInfo(hitPoint, _owner->attackPower, !attackRight);
	}
	/* Make damage */
	float damage = oAttack::getDamage(target);
	target->properties["hp"] -= damage;
	if (damaged)
	{
		damaged(_owner, target, damage);
	}
	return true;
}

oHit::oHit( oUnit* unit ):
oAction(oID::ActionHit, oID::PriorityHit, unit),
_effect(nullptr),
_hitFromRight(true),
_attackPower(),
_hitPoint()
{
	int hitEffect = _owner->getUnitDef()->hitEffect;
	if (hitEffect != oEffectType::None)
	{
		_effect = oEffect::create(hitEffect);
		_effect->attachTo(_owner);
		_effect->retain();
	}
	oModel* model = unit->getModel();
	model->handlers[oID::AnimationHit] += std::make_pair(this, &oHit::onAnimationEnd);
}

oHit::~oHit()
{
	oModel* model = _owner->getModel();
	model->handlers[oID::AnimationHit] -= std::make_pair(this, &oHit::onAnimationEnd);
}

void oHit::run()
{
	oAction::run();
	oModel* model = _owner->getModel();
	model->setLook(oID::LookSad);
	model->setLoop(false);
	//model->setRecovery(0.05f);
	model->setSpeed(1.0f);
	model->play(oID::AnimationHit);
	CCPoint key = CCPointApplyAffineTransform(_hitPoint, _owner->parentToNodeTransform());
	if (_effect)
	{
		_effect->setOffset(key)->start();
	}
	_owner->setVelocityX(_hitFromRight ? -_attackPower.x : _attackPower.x);
	_owner->setVelocityY(_attackPower.y);
	_owner->setFaceRight(_hitFromRight);
	if (actionStart)
	{
		actionStart(this);
	}
}

void oHit::update( float dt )
{ }

void oHit::setHitInfo( const CCPoint& hitPoint, const CCPoint& attackPower, bool hitFromRight )
{
	_hitPoint = hitPoint;
	_hitFromRight = hitFromRight;
	_attackPower = attackPower;
}

void oHit::onAnimationEnd( oModel* model )
{
	if (oAction::isDoing())
	{
		this->stop();
		if (actionEnd)
		{
			actionEnd(this);
		}
	}
}

void oHit::stop()
{
	oAction::stop();
	_owner->getModel()->stop();
}

oAction* oHit::create( oUnit* unit )
{
	return new oHit(unit);
}

oDie::oDie( oUnit* unit ):
oAction(oID::ActionDie, oID::PriorityDie, unit)
{
	oModel* model = unit->getModel();
	model->handlers[oID::AnimationDie] += std::make_pair(this, &oDie::onAnimationEnd);
}

oDie::~oDie()
{
	oModel* model = _owner->getModel();
	model->handlers[oID::AnimationDie] -= std::make_pair(this, &oDie::onAnimationEnd);
}

void oDie::run()
{
	oAction::run();
	oModel* model = _owner->getModel();
	model->setLook(oID::LookDead);
	model->setLoop(false);
	//model->setRecovery(0.05f);
	model->setSpeed(1.0f);
	model->play(oID::AnimationDie);
	int hitEffect = _owner->getUnitDef()->hitEffect;
	if (hitEffect != oEffectType::None)
	{
		oEffect* effect = oEffect::create(hitEffect);
		effect->attachTo(_owner)->autoRemove()->start();
	}
	if (actionStart)
	{
		actionStart(this);
	}
}

void oDie::update( float dt )
{ }

void oDie::stop()
{
	oAction::stop();
	_owner->getModel()->stop();
}

void oDie::onAnimationEnd( oModel* model )
{
	if (oAction::isDoing())
	{
		this->stop();
		if (actionEnd)
		{
			actionEnd(this);
		}
	}
}

oAction* oDie::create( oUnit* unit )
{
	return new oDie(unit);
}

// Initializer
const oActionHelper::oActionFunc oActionHelper::creates[] = 
{
	&oWalk::create,
	&oTurn::create,
	&oMeleeAttack::create,
	&oRangeAttack::create,
	&oIdle::create,
	&oStop::create,
	&oJump::create,
	&oHit::create,
	&oDie::create
};

const uint32 oActionHelper::MAX_BASE_ACTION = sizeof(creates) / sizeof(oActionFunc);

oAction* oActionHelper::create( int id, oUnit* unit )
{
	if (0 <= id && id < MAX_BASE_ACTION)
	{
		return creates[id](unit);
	}
	return nullptr;
}

const string oID::AnimationWalk("walk");
const string oID::AnimationAttack("attack");
const string oID::AnimationIdle("idle");
const string oID::AnimationJump("jump");
const string oID::AnimationHit("hit");
const string oID::AnimationDie("die");

const int oID::ActionWalk = 0;
const int oID::ActionTurn = 1;
const int oID::ActionMeleeAttack = 2;
const int oID::ActionRangeAttack = 3;
const int oID::ActionIdle = 4;
const int oID::ActionStop = 5;
const int oID::ActionJump = 6;
const int oID::ActionHit = 7;
const int oID::ActionDie = 8;
const int oID::ActionUser = 9;

const int oID::PriorityIdle = 0;
const int oID::PriorityWalk = 1;
const int oID::PriorityTurn = 2;
const int oID::PriorityJump = 2;
const int oID::PriorityAttack = 3;
const int oID::PriorityStop = 2147483647;
const int oID::PriorityHit = 4;
const int oID::PriorityDie = 5;

const float oID::ReactionWalk = 0.05f;
const float oID::ReactionIdle = 0.2f;
const float oID::ReactionJump = 0.05f;

const string oID::LookHappy("happy");
const string oID::LookFight("fight");
const string oID::LookSad("sad");
const string oID::LookDead("dead");

NS_DOROTHY_PLATFORM_END
