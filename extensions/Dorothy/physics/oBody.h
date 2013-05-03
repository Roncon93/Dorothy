#ifndef __DOROTHY_PHYSICS_OBODY_H__
#define __DOROTHY_PHYSICS_OBODY_H__

NS_DOROTHY_BEGIN

class oSensor;
class oWorld;
class oBodyDef;
class oFixtureDef;

class oBody: public CCNode
{
public:
	virtual ~oBody();
	virtual void onEnter();
	virtual void onExit();
	PROPERTY_READONLY(oWorld*, World);
	PROPERTY_READONLY(oBodyDef*, BodyDef);
	PROPERTY_READONLY(b2Body*, B2Body);
	PROPERTY_READONLY(b2Vec2, Velocity);
	PROPERTY_NAME(float, VelocityX);
	PROPERTY_NAME(float, VelocityY);
	PROPERTY_VIRTUAL(int, _group, Group);
	void setVelocity(float x, float y);
	void setVelocity(const b2Vec2& velocity);
	void setPosition(float x, float y);
	virtual void setRotation(float var); 
	virtual void setPosition(const CCPoint& var);
	oSensor* getSensorByTag(uint32 tag);
	bool removeSensorByTag(uint32 tag);
	bool removeSensor(oSensor* sensor);
	b2Fixture* attach(b2FixtureDef* fixtureDef);
	oSensor* attachSensor(int tag, b2FixtureDef* fixtureDef);
	void destroy();
	static oBody* create(oWorld* world, oBodyDef* bodyDef);
protected:
	oBody(oWorld* world, oBodyDef* bodyDef);
	virtual void updatePhysics();
	b2Body* _bodyB2;// weak reference
	oWorld* _world;
private:
	oRef<oBodyDef> _bodyDef;
	oRef<CCArray> _sensors;
	friend class oWorld;
};

NS_DOROTHY_END

#endif // __DOROTHY_PHYSICS_OBODY_H__