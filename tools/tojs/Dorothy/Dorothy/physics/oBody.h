#ifndef __DOROTHY_PHYSICS_OBODY_H__
#define __DOROTHY_PHYSICS_OBODY_H__

NS_DOROTHY_BEGIN

class oSensor;
class oWorld;
class oBodyDef;

class oBody: public CCNode
{
public:
	PROPERTY_READONLY(oWorld*, World);
	PROPERTY_READONLY(oBodyDef*, BodyDef);
	PROPERTY_READONLY(b2Vec2, Velocity);
	PROPERTY_NAME(float, VelocityX);
	PROPERTY_NAME(float, VelocityY);
	PROPERTY(int, _group, Group);
	void setVelocity(float x, float y);
	void setVelocity(const b2Vec2& velocity);
	void setPosition(float x, float y);
	oSensor* getSensorByTag(uint32 tag);
	bool removeSensorByTag(uint32 tag);
	bool removeSensor(oSensor* sensor);
	void attach(oFixtureDef* fixtureDef);
	oSensor* attachSensor(int tag, oFixtureDef* fixtureDef);
};

NS_DOROTHY_END

#endif // __DOROTHY_PHYSICS_OBODY_H__