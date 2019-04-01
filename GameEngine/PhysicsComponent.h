//#ifndef _PHYSICSCOMPONENT_H
//#define _PHYSICSCOMPONENT_H
#pragma once
#include "Component.h"
#include "ComponentTypes.h"
#include "GlobalDeclarations.h"
#include "SDL2-2.0.8\SDL.h"
#include "Box2D\Box2D.h"
#include "CollisionListener.h"

struct bodyUserData
{
	int bodyType;
	int id;
};
class PhysicsComponent : public Component
{
public:
	PhysicsComponent(void) : Component(CT_PhysicsComponent)
	{
	}
	~PhysicsComponent();

	void init(); 
	void update();
	void render();
	void ReSetGravity(float x, float y);

	void createBody(int x, int y, int w, int h, GameObject* gb,bool dyn = true);
	void SetVelocityIterator(int vItr) { m_velocityIterator = vItr; }
	int  GetVelocityIterator() { return m_velocityIterator; }
	void SetPositionIterator(int pItr) { m_positionIterator = pItr; }
	int  GetPositionIterator() { return m_positionIterator; }

	b2Vec2 GetBodyPositions();
	b2Body* GetBody();
	float GetHeight() { return height; }
	float GetWidth() { return width; }
private:
	int m_velocityIterator;
	int m_positionIterator;
	float timeStep;
	b2Body* m_body;
	float height, width;
	
};

//#endif
