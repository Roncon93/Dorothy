#ifndef __DOROTHY_PLATFORM_OBULLET_DEF_H__
#define __DOROTHY_PLATFORM_OBULLET_DEF_H__

#include "Dorothy/physics/oBodyDef.h"
#include "Dorothy/model/oFace.h"

NS_DOROTHY_BEGIN
class oWorld;
NS_DOROTHY_END

NS_DOROTHY_PLATFORM_BEGIN
class oBullet;
class oUnit;

class oBulletDef: public CCObject
{
public:
	void setVelocity(float angle, float speed);
	PROPERTY_REF(b2Vec2, _velocity, Velocity);
	PROPERTY_NAME(bool, IsHighSpeed);
	PROPERTY_NAME(float, GravityScale);
	PROPERTY_NAME(oFace*, Face);
	uint32 type;
	int endEffect;
	float lifeTime;
	float damageRadius;
	static oBulletDef* create();
	void setAsCircle(float radius);
	oBodyDef* getBodyDef() const;
	oBullet* toBullet(oWorld* world, oUnit* unit);
	static const int SENSOR_TAG;
protected:
	oBulletDef();
	oRef<oBodyDef> _bodyDef;
	oRef<oFace> _face;
};

NS_DOROTHY_PLATFORM_END

#endif // __DOROTHY_PLATFORM_OBULLET_DEF_H__