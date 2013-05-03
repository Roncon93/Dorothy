#ifndef __DOROTHY_PLATFORM_OPLATFORMDEFINE_H__
#define __DOROTHY_PLATFORM_OPLATFORMDEFINE_H__

#define NS_DOROTHY_PLATFORM_BEGIN namespace Dorothy { namespace Platform {
#define NS_DOROTHY_PLATFORM_END }}

NS_DOROTHY_PLATFORM_BEGIN

enum oAttackType
{
	e_attackMelee = 0,
	e_attackRange = 1
};
enum oAttackTarget
{
	e_targetOne = 0,
	e_targetMulti = 1
};
enum oRelation
{
	e_unkown = 0,
	e_friend = 1<<0,
	e_neutral = 1<<1,
	e_enemy = 1<<2,
	e_anyRelation = e_friend|e_neutral|e_enemy
};
enum oDamageType
{
	e_damageOne = 0,
	e_damageTwo = 1,
	e_damageThree = 2,
	e_damageFour = 3,
	e_damageFive = 4,
	e_damageSix = 5
};
enum oDefenceType
{
	e_defenceOne = 0,
	e_defenceTwo = 1<<16,
	e_defenceThree = 2<<16,
	e_defenceFour = 3<<16,
	e_defenceFive = 4<<16,
	e_defenceSix = 5<<16
};

/*
Target Allow
	oRelation
		e_unkown 0
		e_friend 1<<0
		e_neutral 1<<1
		e_enemy 1<<2
	oGroup
		oSharedData.getTerrainGroup() 1<<3
*/
class oTargetAllow
{
public:
	oTargetAllow();
	void allowTerrain(bool var);
	bool isTerrainAllowed() const;
	void allow(oRelation flag);
	void disallow(oRelation flag);
	bool isAllow(oRelation flag);
protected:
	uint32 _flag;
};

NS_DOROTHY_PLATFORM_END

#endif // __DOROTHY_PLATFORM_OPLATFORMDEFINE_H__