#ifndef __DOROTHY_PLATFORM_OUNIT_H__
#define __DOROTHY_PLATFORM_OUNIT_H__

#include "Dorothy/model/oModel.h"
#include "Dorothy/physics/oBody.h"
#include "Dorothy/platform/oUnitDef.h"
#include "Dorothy/platform/oProperty.h"
#include "Dorothy/platform/oAINode.h"
#include "Dorothy/platform/oBulletDef.h"

NS_DOROTHY_BEGIN
class oSensor;
NS_DOROTHY_END

NS_DOROTHY_PLATFORM_BEGIN
class oAction;
class oProperty;
class oInstinct;

class oUnit: public oBody
{
	typedef unordered_map<int, oOwn<oAction>> oActionMap;
	typedef hash_strmap<oProperty*> oPropertyMap;
public:
	//Class properties
	PROPERTY_NAME(oModel*, Model);
	PROPERTY(float, _detectDistance, DetectDistance);
	PROPERTY_REF(CCSize, _attackRange, AttackRange);
	PROPERTY_BOOL(_isFaceRight, FaceRight);
	PROPERTY_READONLY(oSensor*, GroundSensor);
	PROPERTY_READONLY(oSensor*, DetectSensor);
	PROPERTY_READONLY(oSensor*, AttackSensor);
	PROPERTY_READONLY(oUnitDef*, UnitDef);
	PROPERTY_READONLY(oAction*, CurrentAction);
	PROPERTY_NAME(oBulletDef*, BulletDef);
	PROPERTY_READONLY(float, Width);
	PROPERTY_READONLY(float, Height);
	//
	virtual void setGroup( int group );
	virtual void update( float dt );
	//Actions
	oAction* attachAction(int id);
	void attachAction(oAction* action);
	oAction* getAction(int id) const;
	bool doIt(int id);
	//
	bool isOnSurface() const;
	void onActionEnd(oAction* action);
	static oUnit* create(oWorld* world, oUnitDef* unitDef);
	//Named properties
	class oPropertySet
	{
	public:
		~oPropertySet();
		oProperty& operator[](const string& name);
		const oProperty& operator[](const string& name) const;
		oProperty* get(const string& name) const;
		void remove(const string& name);
		void clear();
	private:
		void setOwner(oUnit* owner);
		oUnit* _owner;
		oPropertyMap _items;
		friend class oUnit;
	} properties;
	//Dynamic properties
	float sensity;
	float move;
	float moveSpeed;
	float jump;
	float maxHp;
	float attackBase;
	float attackBonus;
	float attackFactor;
	float attackSpeed;
	CCPoint attackPower;
	oAttackType attackType;
	oAttackTarget attackTarget;
	oTargetAllow targetAllow;
	oDamageType damageType;
	oDefenceType defenceType;
	//Instinct
	class oInstinctSet
	{
	public:
		void add(oInstinct* instinct);
		void remove(oInstinct* instinct);
		void reinstall();
		void clear();
	private:
		void setOwner(oUnit* owner);
		oUnit* _owner;
		oRefVector<oInstinct> _instincts;
		friend class oUnit;
	} instincts;
	//Conditioned Reflex
	PROPERTY_NAME(oAILeaf*, ReflexArc);
protected:
	oUnit(oWorld* world, oUnitDef* unitDef);
private:
	oRef<oUnitDef> _unitDef;
	oRef<oAILeaf> _reflexArc;
	oRef<oBulletDef> _bulletDef;
	oRef<oModel> _model;
	CCSize _size;
	oSensor* _groundSensor;
	oSensor* _detectSensor;
	oSensor* _attackSensor;
	oAction* _currentAction;
	oActionMap _actions;
};

NS_DOROTHY_PLATFORM_END

#endif // __DOROTHY_PLATFORM_OUNIT_H__