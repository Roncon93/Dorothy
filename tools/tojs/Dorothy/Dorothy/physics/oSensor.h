#ifndef __DOROTHY_PHYSICS_OSENSOR_H__
#define __DOROTHY_PHYSICS_OSENSOR_H__

NS_DOROTHY_BEGIN

class oBody;

class oSensor: public CCObject
{
public:
	PROPERTY(bool, _enable, Enable);
	PROPERTY_READONLY(int, Tag);
	PROPERTY_READONLY(oBody*, Owner);
	bool sensed() const;
	//PROPERTY_READONLY_REF(oRefVector<oBody>, SensedBodies);
	bool contains(oBody* body);
};

NS_DOROTHY_END

#endif // __DOROTHY_PHYSICS_OSENSOR_H__