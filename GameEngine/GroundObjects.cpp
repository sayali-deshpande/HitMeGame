#include "GroundObjects.h"

GroundObjects::GroundObjects(int x, int y, int w, int h)
	:xPos(x),yPos(y),height(h),width(w)
{
}

GroundObjects::~GroundObjects()
{
}

void GroundObjects::init()
{
	//Add Components for GroundObject
	//GameManager::Get()->GetObjectManager().addObject(this);
	
	m_sprite = new SpriteComponent();
	m_physics = new PhysicsComponent();
	AddComponent(m_sprite);
	AddComponent(m_physics);
	SetType(OT_StaticPlayer);
	createBody(xPos, yPos, width, height, this, false);
	GetBody()->SetAwake(false);
	bodyUserData *bud = new bodyUserData();
	bud->bodyType = OT_StaticPlayer;
	GetBody()->SetUserData(bud);
	m_sprite->LoadTexture("../assets/brick.png");
	m_sprite->height = height;
	m_sprite->width = width;
	//g->addObject(this);
}

void GroundObjects::update()
{
}

void GroundObjects::OnEvent(InputKey key/*const Event & e*/)
{
}

void GroundObjects::PassMessage(std::string message)
{
}
