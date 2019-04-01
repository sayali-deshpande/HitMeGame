//#ifndef _GROUNDOBJECTS_H
//#define _GROUNDOBJECTS_H
#pragma once
//#include "GameManager.h"
#include "GameObject.h"
#include "SpriteComponent.h"
#include "PhysicsComponent.h"
#include "GlobalDeclarations.h"
#include "BroadCaster.h"
#include "ComponentTypes.h"
#include "Event.h"
#include "Listener.h"

class GroundObjects : public GameObject
{
public:
	GroundObjects(int x, int y, int h, int w);
	~GroundObjects();

	void init();
	void update();

	virtual void OnEvent(InputKey key/*const Event &e*/); //overridden function
	virtual void PassMessage(std::string message); //overridden function
private:
	GroundObjects *m_obj;
	int xPos, yPos, height, width;
	SpriteComponent* m_sprite;
	PhysicsComponent* m_physics;
};
//#endif
