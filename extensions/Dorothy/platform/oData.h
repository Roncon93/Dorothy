#ifndef __DOROTHY_PLATFORM_ODATA_H__
#define __DOROTHY_PLATFORM_ODATA_H__

NS_DOROTHY_PLATFORM_BEGIN

class oUnit;
class oPlatformWorld;

class oData
{
public:
	void apply(oPlatformWorld* world);
	void setRelation(int groupA, int groupB, oRelation relation);
	oRelation getRelation(int groupA, int groupB) const;
	oRelation getRelation(oUnit* unitA, oUnit* unitB) const;
	PROPERTY_READONLY(int, HideGroup);
	PROPERTY_READONLY(int, SensePlayerGroup);
	PROPERTY_READONLY(int, TerrainGroup);
	PROPERTY_READONLY(int, SenseAllGroup);
	void setDamageFactor(oDamageType damageType, oDefenceType defenceType, float bounus);
	float getDamageFactor(oDamageType damageType, oDefenceType defenceType) const;
	bool isPlayerUnit(oBody* body);
	bool isTerrain(oBody* body);
	static oData* shared();
private:
	unordered_map<uint32, oRelation> _relationMap;
	unordered_map<uint32, float> _damageBounusMap;
};

#define oSharedData (*oData::shared())

NS_DOROTHY_PLATFORM_END

#endif // __DOROTHY_PLATFORM_ODATA_H__