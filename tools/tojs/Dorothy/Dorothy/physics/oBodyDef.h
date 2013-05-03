#ifndef __DOROTHY_PHYSICS_OBODYDEF_H__
#define __DOROTHY_PHYSICS_OBODYDEF_H__

class oFixtureDef
{};

NS_DOROTHY_BEGIN

class oBody;
class oWorld;

typedef vector<b2Vec2> b2Vec2Vector;

class oBodyDef: public CCObject
{
public:
	enum
	{
		Static = b2_staticBody,
		Dynamic = b2_dynamicBody,
		Kinematic = b2_kinematicBody
	};
	void setType(int type);
	void setFixedRotation(bool fixed);
	void setIsBullet(bool isBullet);
	void setGravityScale(float scale);
	static oFixtureDef* polygon(
		const b2Vec2& center,
		float width,
		float height,
		float angle = 0.0f,
		float density = 0.0f,
		float friction = 0.2f,
		float restitution = 0.0f);
	void attachPolygon(
		const b2Vec2& center,
		float width,
		float height,
		float angle = 0.0f,
		float density = 0.0f,
		float friction = 0.2f,
		float restitution = 0.0f);
	static oFixtureDef* polygon(
		float width,
		float height,
		float density = 0.0f,
		float friction = 0.2f,
		float restitution = 0.0f);
	void attachPolygon(
		float width,
		float height,
		float density = 0.0f,
		float friction = 0.2f,
		float restitution = 0.0f);
	static oFixtureDef* polygon(
		const b2Vec2Vector& vertices,
		float density = 0.0f,
		float friction = 0.2f,
		float restitution = 0.0f);
	void attachPolygon(
		const b2Vec2Vector& vertices,
		float density = 0.0f,
		float friction = 0.2f,
		float restitution = 0.0f);
	static oFixtureDef* loop(
		const b2Vec2Vector& vertices,
		float friction = 0.2f,
		float restitution = 0.0f);
	void attachLoop(
		const b2Vec2Vector& vertices,
		float friction = 0.2f,
		float restitution = 0.0f);
	static oFixtureDef* circle(
		const b2Vec2& center,
		float radius,
		float density = 0.0f,
		float friction = 0.2f,
		float restitution = 0.0f);
	void attachCircle(
		const b2Vec2& center,
		float radius,
		float density = 0.0f,
		float friction = 0.2f,
		float restitution = 0.0f);
	static oFixtureDef* circle(
		float radius,
		float density = 0.0f,
		float friction = 0.2f,
		float restitution = 0.0f);
	void attachCircle(
		float radius,
		float density = 0.0f,
		float friction = 0.2f,
		float restitution = 0.0f);
	static oFixtureDef* chain(
		const b2Vec2Vector& vertices,
		float friction = 0.2f,
		float restitution = 0.0f);
	void attachChain(
		const b2Vec2Vector& vertices,
		float friction = 0.2f,
		float restitution = 0.0f);
	void attachPolygonSensor(
		int tag,
		float width,
		float height);
	void attachPolygonSensor(
		int tag,
		float width,
		float height,
		const b2Vec2& center,
		float angle = 0.0f);
	void attachPolygonSensor(
		int tag,
		const b2Vec2Vector& vertices);
	void attachCircleSensor(
		int tag,
		const b2Vec2& center,
		float radius);
	void attachCircleSensor(
		int tag,
		float radius);
	void clearFixtures();
	static oBodyDef* create();
	oBody* toBody(oWorld* world, int group, float x, float y, float angle = 0.0f);
};

NS_DOROTHY_END

#endif // __DOROTHY_PHYSICS_OBODYDEF_H__
