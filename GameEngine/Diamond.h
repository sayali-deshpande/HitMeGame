#pragma once
#include "GameObject.h"
#include "SpriteComponent.h"
#include "PhysicsComponent.h"
#include "GlobalDeclarations.h"
#include "BroadCaster.h"
#include "ComponentTypes.h"
#include "Event.h"
#include "Listener.h"

class Diamond : public GameObject, public Listener
{
public:
	Diamond(int x, int y, int w, int h);
	~Diamond();

	void init();
	void update();
	void render();

	void RemoveDiamond();

	virtual void OnEvent(InputKey key/*const Event &e*/); //overridden function
	virtual void PassMessage(std::string message); //overridden function

	static int objectId;
private:
	Diamond *m_obj;
	int xPos, yPos, height, width;
	SpriteComponent* m_sp;
	PhysicsComponent* m_phy;
};