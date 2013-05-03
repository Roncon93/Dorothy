#ifndef __DOROTHY_PLATFORM_OACTION_H__
#define __DOROTHY_PLATFORM_OACTION_H__

NS_DOROTHY_BEGIN
class oModel;
class oBody;
class oEffect;
NS_DOROTHY_END

NS_DOROTHY_PLATFORM_BEGIN
class oUnit;
class oAction;
class oBullet;
typedef Delegate<void (oAction* action)> oActionHandler;
typedef Delegate<void (oUnit* source, oUnit* target, float damage)> oDamageHandler;

class oAction
{
public:
	oAction(int id, int priority, oUnit* owner);
	virtual ~oAction();
	float reaction;
	int getId() const;
	int getPriority() const;
	bool isDoing() const;
	oUnit* getOwner() const;
	oActionHandler actionStart;
	oActionHandler actionEnd;
	virtual bool isAvailable();
	virtual void run();
	virtual void update(float dt);
	virtual void stop();
	static oAction* create(int id, oUnit* unit);
protected:
	oUnit* _owner;
private:
	bool _isDoing;
	int _id;
	int _priority;
	float _reflexDelta;
};

struct oID
{
	static const string AnimationWalk;
	static const string AnimationAttack;
	static const string AnimationIdle;
	static const string AnimationJump;
	static const string AnimationHit;
	static const string AnimationDie;

	static const int ActionWalk;
	static const int ActionTurn;
	static const int ActionMeleeAttack;
	static const int ActionRangeAttack;
	static const int ActionIdle;
	static const int ActionStop;
	static const int ActionJump;
	static const int ActionHit;
	static const int ActionDie;
	static const int ActionUser;

	static const int PriorityWalk;
	static const int PriorityTurn;
	static const int PriorityJump;
	static const int PriorityAttack;
	static const int PriorityIdle;
	static const int PriorityStop;
	static const int PriorityHit;
	static const int PriorityDie;

	static const float ReactionWalk;
	static const float ReactionIdle;
	static const float ReactionJump;

	static const string LookHappy;
	static const string LookFight;
	static const string LookSad;
	static const string LookDead;
};

class oWalk: public oAction
{
public:
	oWalk(oUnit* unit);
	virtual bool isAvailable();
	virtual void run();
	virtual void update(float dt);
	virtual void stop();
	static oAction* create(oUnit* unit);
};

class oTurn: public oAction
{
public:
	oTurn(oUnit* unit);
	virtual void run();
	static oAction* create(oUnit* unit);
};

class oAttack: public oAction
{
public:
	oAttack(int id, oUnit* unit);
	virtual ~oAttack();
	virtual void run();
	virtual void update(float dt);
	virtual void stop();
	void onAnimationEnd(oModel* model);
	float getDamage(oUnit* target);
	virtual void onAttack() = 0;
	oDamageHandler damaged;
	static bool usePreciseHit;
	static CCPoint getHitPoint(oBody* self, oBody* target, b2Shape* selfShape);
protected:
	float _current;
	float _attackDelay;
	float _attackEffectDelay;
};

class oMeleeAttack: public oAttack
{
public:
	oMeleeAttack(oUnit* unit);
	static oAction* create(oUnit* unit);
protected:
	virtual void onAttack();
	b2PolygonShape _polygon;
};

class oRangeAttack: public oAttack
{
public:
	oRangeAttack(oUnit* unit);
	static oAction* create(oUnit* unit);
	bool onHitTarget(oBullet* bullet, oUnit* target);
protected:
	virtual void onAttack();
};

class oIdle: public oAction
{
public:
	oIdle(oUnit* unit);
	virtual void run();
	virtual void update(float dt);
	virtual void stop();
	static oAction* create(oUnit* unit);
};

class oJump: public oAction
{
public:
	oJump(oUnit* unit);
	virtual bool isAvailable();
	virtual void run();
	virtual void update(float dt);
	virtual void stop();
	static oAction* create(oUnit* unit);
private:
	float _current;
};

class oStop: public oAction
{
public:
	oStop(oUnit* unit);
	virtual void run();
	static oAction* create(oUnit* unit);
};

class oHit: public oAction
{
public:
	oHit(oUnit* unit);
	virtual ~oHit();
	virtual void run();
	virtual void update( float dt );
	virtual void stop();
	void setHitInfo(const CCPoint& hitPoint, const CCPoint& attackPower, bool hitFromRight);
	void onAnimationEnd(oModel* model);
	static oAction* create(oUnit* unit);
protected:
	bool _hitFromRight;
	oEffect* _effect;
	CCPoint _hitPoint;
	CCPoint _attackPower;
};

class oDie: public oAction
{
public:
	oDie(oUnit* unit);
	virtual ~oDie();
	virtual void run();
	virtual void update(float dt);
	virtual void stop();
	static oAction* create(oUnit* unit);
	void onAnimationEnd(oModel* model);
};

class oActionHelper
{
public:
	typedef oAction* (*oActionFunc)(oUnit* unit);
	static oAction* create(int id, oUnit* unit);
private:
	static const oActionFunc creates[];
	static const uint32 MAX_BASE_ACTION; 
};

NS_DOROTHY_PLATFORM_END

#endif // __DOROTHY_PLATFORM_OACTION_H__
