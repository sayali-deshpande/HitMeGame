#pragma once
//#ifndef _COLLISIONLISTENER_H
//#define _COLLISIONLISTENER_H

#include "Box2D/Box2D.h"

class CollisionListener : public b2ContactListener
{
public:
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
};

//#endif