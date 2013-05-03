#ifndef __DOROTHY_PHYSICS_OWORLD_H__
#define __DOROTHY_PHYSICS_OWORLD_H__

NS_DOROTHY_BEGIN

class oBody;
class oSensor;

class oWorld: public CCLayer
{
public:
	oWorld();
	void setIterations(int velocityIter, int positionIter);
	void setGravity(const b2Vec2& gravity);
	b2Vec2 getGravity() const;
	//void queryAABB(const b2AABB& aabb, const function<bool(oBody*)>& callback);
	void setShouldContact(int groupA, int groupB, bool contact);
	bool getShouldContact(int groupA, int groupB) const;
	static float b2Factor;
	oWorld* create();
};

NS_DOROTHY_END

#endif // __DOROTHY_PHYSICS_OWORLD_H__
