#ifndef __DOROTHY_PLATFORM_OAI_H__
#define __DOROTHY_PLATFORM_OAI_H__

NS_DOROTHY_PLATFORM_BEGIN

class oCompare
{
public:
	virtual ~oCompare(){}
	virtual bool getResult(float leftValue) = 0;
};

class oTrue: public oCompare
{
public:
	virtual bool getResult(float leftValue) { return true; }
};

class oFalse: public oCompare
{
public:
	virtual bool getResult(float leftValue) { return false; }
};

class oExpCompare: public oCompare
{
public:
	oExpCompare(oCompare* left, uint32 op, oCompare* right);
	virtual ~oExpCompare();
	enum {Or = 0, And = 1};
	virtual bool getResult(float leftValue);
private:
	bool _and;
	oCompare* _left;
	oCompare* _right;
};

class oValCompare: public oCompare
{
public:
	enum
	{
		Equal = 0,
		Less = 1,
		LessEqual = 2,
		Greater = 3,
		GreaterEqual = 4
	};
	oValCompare(uint32 op, float rightValue);
	virtual bool getResult(float leftValue);
private:
	uint32 _op;
	float _rightValue;
};

class oUnit;

class oAI
{
public:
	static oUnit* self();
	static bool conditionedReflex(oUnit* unit);

	/*0*/static bool condition_UnitCountCompare(oRelation relation, oCompare* compare);
	/*1*/static bool condition_UnitTypeCountCompare(oRelation relation, uint32 type, oCompare* compare);
	/*2*/static bool condition_UnitDistanceCompareCountCompare(oRelation relation, oCompare* compareDistance, oCompare* compareCount);
	/*3*/static bool condition_UnitHpCompareCountCompare(oRelation relation, oCompare* compareHp, oCompare* compareCount);
	/*4*/static bool condition_UnitHpPercentCompareCountCompare(oRelation relation, oCompare* comparePercent, oCompare* compareCount);
	/*5*/static bool condition_UnitPropertyCompareCountCompare(oRelation relation, const string& name, oCompare* compareProperty, oCompare* compareCount);

	/*6*/static bool condition_SelfHpCompare(oCompare* compare);
	/*7*/static bool condition_SelfHpPercentCompare(oCompare* compare);
	/*8*/static bool condition_SelfPropertyCompare(const string& name, oCompare* compare);

	/*9*/static bool condition_AnyUnitDoingAction(oRelation relation, uint32 actionId);
	/*10*/static bool condition_AnyUnitDistanceCompare(oRelation relation, oCompare* compare);
	/*11*/static bool condition_AnyUnitHpCompare(oRelation relation, oCompare* compare);
	/*12*/static bool condition_AnyUnitHpPercentCompare(oRelation relation, oCompare* compare);
	/*13*/static bool condition_AnyUnitPropertyCompare(oRelation relation, const string& name, oCompare* compare);

	/*14*/static bool condition_NearestUnitDoingAction(oRelation relation, uint32 actionId);
	/*15*/static bool condition_NearestUnitHpCompare(oRelation relation, oCompare* compare);
	/*16*/static bool condition_NearestUnitHpPercentCompare(oRelation relation, oCompare* compare);
	/*17*/static bool condition_NearestUnitPropertyCompare(oRelation relation, const string& name, oCompare* compare);

	/*18*/static bool condition_UnitWithTagDoingAction(int tag, uint32 actionId);
	/*19*/static bool condition_UnitWithTagDistanceCompare(int tag, oCompare* compare);
	/*20*/static bool condition_UnitWithTagHpCompare(int tag, oCompare* compare);
	/*21*/static bool condition_UnitWithTagHpPercentCompare(int tag, oCompare* compare);
	/*22*/static bool condition_UnitWithTagPropertyCompare(int tag, const string& name, oCompare* compare);

	/*23*/static bool condition_SelfFaceLeft();
	/*24*/static bool condition_NearestUnitFaceLeft(oRelation relation);
	/*25*/static bool condition_UnitWithTagFaceLeft(int tag);

	/*26*/static bool condition_NearestUnitAtUnitLeft(oRelation relation);
	/*27*/static bool condition_UnitWithTagAtUnitLeft(int tag);

	/*28*/static bool condition_LastChangedInstinctPropertyDeltaCompare(oCompare* compare);

	static float getLastDeltaInstinctProperty();
private:
	static const vector<oUnit*>& getUnitsByRelation(oRelation relation);
	static oUnit* getNearestUnitByRelation(oRelation relation);
	static oUnit* getUnitByTag(int tag);

	static oUnit* _self;

	static oUnit* _nearestUnit;
	static oUnit* _nearestFriend;
	static oUnit* _nearestEnemy;
	static oUnit* _nearestNeutral;

	static vector<oUnit*> _friends;
	static vector<oUnit*> _enemies;
	static vector<oUnit*> _neutrals;
	static vector<oUnit*> _detectedUnits;

	static float _lastDeltaInstinctProperty;
	friend class oInstinct;
};

NS_DOROTHY_PLATFORM_END

#endif // __DOROTHY_PLATFORM_OAI_H__
