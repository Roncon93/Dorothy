#include "Dorothy/const/oDefine.h"
#include "Dorothy/physics/oWorld.h"
#include "Dorothy/physics/oBody.h"
#include "Dorothy/physics/oSensor.h"

NS_DOROTHY_BEGIN

void oContactListener::oSensorPair::retain()
{
	sensor->getOwner()->retain();
	sensor->retain();
	body->retain();
}

void oContactListener::oSensorPair::release()
{
	sensor->getOwner()->release();
	sensor->release();
	body->release();
}

bool oWorld::oQueryAABB::ReportFixture( b2Fixture* fixture )
{
	if (!fixture->IsSensor())
	{
		oBody* body = (oBody*)fixture->GetBody()->GetUserData();
		if (results.empty() || results.back() != body)
		{
			results.push_back(body);
		}
	}
	return true;
}

float oWorld::b2Factor = 100.0f;

oWorld::oWorld():
_world(b2Vec2(0,-10)),
_velocityIterations(1),
_positionIterations(1),
_contactListner(new oContactListener()),
_contactFilter(new oContactFilter())
{
	_world.SetContactFilter(_contactFilter);
	_world.SetContactListener(_contactListner);
	for (int i = 0; i < 16; i++)
	{
		_filters[i].groupIndex = i;
		_filters[i].categoryBits = 1<<i;
		_filters[i].maskBits = 0;
	}
	CCLayer::scheduleUpdate();
}

oWorld::~oWorld()
{
	for (b2Body* b = _world.GetBodyList();b;b = b->GetNext())
	{
		oBody* body = (oBody*)b->GetUserData();
		if (body)
		{
			body->_bodyB2 = nullptr;
			body->_sensors->removeAllObjects();
		}
	}
}

b2World* oWorld::getB2World()
{
	return &_world;
}

void oWorld::setIterations( int velocityIter, int positionIter )
{
	_velocityIterations = velocityIter;
	_positionIterations = positionIter;
}

void oWorld::setGravity( const b2Vec2& gravity )
{
	_world.SetGravity(gravity);
}

b2Vec2 oWorld::getGravity() const
{
	return _world.GetGravity();
}

void oWorld::update( float dt )
{
	const float maxDeltaTime = 1.0f/30;
	_world.Step(dt > maxDeltaTime ? maxDeltaTime : dt, _velocityIterations, _positionIterations);
	for (b2Body* b = _world.GetBodyList();b;b = b->GetNext())
	{
		oBody* body = (oBody*)b->GetUserData();
		body->updatePhysics();
	}
	_contactListner->SolveSensors();
}

void oWorld::query( const CCRect& rect, const function<bool(oBody*)>& callback )
{
	b2AABB b2aabb;
	b2aabb.lowerBound.Set(b2Val(rect.getMinX()), b2Val(rect.getMinY()));
	b2aabb.upperBound.Set(b2Val(rect.getMaxX()), b2Val(rect.getMaxY()));
	_world.QueryAABB(&_queryCallback, b2aabb);
	for (oBody* item : _queryCallback.results)
	{
		if (callback(item)) break;
	}
	_queryCallback.results.clear();
}

void oWorld::setShouldContact( int groupA, int groupB, bool contact )
{
	b2Filter& filterA = _filters[groupA];
	b2Filter& filterB = _filters[groupB];
	if (contact)
	{
		filterA.maskBits |= filterB.categoryBits;
		filterB.maskBits |= filterA.categoryBits;
	}
	else
	{
		filterA.maskBits &= (~filterB.categoryBits);
		filterB.maskBits &= (~filterA.categoryBits);
	}
	for (b2Body* b = _world.GetBodyList();b;b = b->GetNext())
	{
		b2Fixture* first = b->GetFixtureList();
		if (first)
		{
			int groupIndex = first->GetFilterData().groupIndex;
			if (groupIndex == groupA)
			{
				first->SetFilterData(_filters[groupA]);
			}
			else if (groupIndex == groupB)
			{
				first->SetFilterData(_filters[groupB]);
			}
			// Some shapes make the fixture list a circular list
			for (b2Fixture* f = first->GetNext();f && f != first;f = f->GetNext())
			{
				int groupIndex = f->GetFilterData().groupIndex;
				if (groupIndex == groupA)
				{
					f->SetFilterData(_filters[groupA]);
				}
				else if (groupIndex == groupB)
				{
					f->SetFilterData(_filters[groupB]);
				}
			}
		}
	}
}

bool oWorld::getShouldContact( int groupA, int groupB ) const
{
	const b2Filter& filterA = _filters[groupA];
	const b2Filter& filterB = _filters[groupB];
	return (filterA.maskBits & filterB.categoryBits) && (filterA.categoryBits & filterB.maskBits);
}

const b2Filter& oWorld::getFilter( int group ) const
{
	return _filters[group];
}

void oWorld::setContactListener( oContactListener* listener )
{
	_contactListner = oOwnMake(listener);
}

void oWorld::setContactFilter( oContactFilter* filter )
{
	_contactFilter = oOwnMake(filter);
}

void oContactListener::PostSolve( b2Contact* contact, const b2ContactImpulse* impulse )
{ }

void oContactListener::PreSolve( b2Contact* contact, const b2Manifold* oldManifold )
{ }

void oContactListener::BeginContact( b2Contact* contact )
{
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();
	oBody* bodyA = (oBody*)fixtureA->GetBody()->GetUserData();
	oBody* bodyB = (oBody*)fixtureB->GetBody()->GetUserData();
	if (!bodyA || !bodyB)
	{
		return;
	}
	if (fixtureA->IsSensor())
	{
		oSensor* sensor = (oSensor*)fixtureA->GetUserData();
		if (sensor && sensor->getEnable() && !fixtureB->IsSensor())
		{
			oSensorPair pair = {sensor, bodyB};
			pair.retain();
			_sensorEnters.push_back(pair);
		}
	}
	else if (fixtureB->IsSensor())
	{
		oSensor* sensor = (oSensor*)fixtureB->GetUserData();
		if (sensor && sensor->getEnable())
		{
			oSensorPair pair = {sensor, bodyA};
			pair.retain();
			_sensorEnters.push_back(pair);
		}
	}
}

void oContactListener::EndContact( b2Contact* contact )
{
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();
	if (fixtureA->IsSensor())
	{
		oSensor* sensor = (oSensor*)fixtureA->GetUserData();
		oBody* bodyB = (oBody*)fixtureB->GetBody()->GetUserData();
		if (sensor && bodyB && sensor->getEnable() && !fixtureB->IsSensor())
		{
			oSensorPair pair = {sensor, bodyB};
			pair.retain();
			_sensorLeaves.push_back(pair);
		}
	}
	else if (fixtureB->IsSensor())
	{
		oSensor* sensor = (oSensor*)fixtureB->GetUserData();
		oBody* bodyA = (oBody*)fixtureA->GetBody()->GetUserData();
		if (sensor && bodyA && sensor->getEnable())
		{
			oSensorPair pair = {sensor, bodyA};
			pair.retain();
			_sensorLeaves.push_back(pair);
		}
	}
}

void oContactListener::SolveSensors()
{
	if (!_sensorEnters.empty())
	{
		for (oSensorPair& pair: _sensorEnters)
		{
			if (pair.sensor->getEnable())
			{
				pair.sensor->add(pair.body);
			}
			pair.release();
		}
		_sensorEnters.clear();
	}
	if (!_sensorLeaves.empty())
	{
		for (oSensorPair& pair: _sensorLeaves)
		{
			if (pair.sensor->getEnable())
			{
				pair.sensor->remove(pair.body);
			}
			pair.release();
		}
		_sensorLeaves.clear();
	}
}

oContactListener::~oContactListener()
{
	for (oSensorPair& pair: _sensorEnters)
	{
		pair.release();
	}
	for (oSensorPair& pair: _sensorLeaves)
	{
		pair.release();
	}
}

bool oContactFilter::ShouldCollide( b2Fixture* fixtureA, b2Fixture* fixtureB )
{
	const b2Filter& filterA = fixtureA->GetFilterData();
	const b2Filter& filterB = fixtureB->GetFilterData();
	return (filterA.maskBits & filterB.categoryBits) && (filterA.categoryBits & filterB.maskBits);
}

NS_DOROTHY_END
