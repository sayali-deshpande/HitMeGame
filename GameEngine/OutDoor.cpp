#include "OutDoor.h"

OutDoor::OutDoor()
{
	xPos = 5;
	yPos = 890;
	width = 50;
	height = 100;
}

OutDoor::~OutDoor()
{
}

void OutDoor::init()
{
	m_sprite = new SpriteComponent();
	m_physics = new PhysicsComponent();
	AddComponent(m_sprite);
	AddComponent(m_physics);
	SetType(OT_ENDDOOR);
	createBody(xPos, yPos, width, height, this, false);
	GetBody()->SetAwake(false);
	bodyUserData *bud = new bodyUserData();
	bud->bodyType = OT_ENDDOOR;
	GetBody()->SetUserData(bud);
	m_sprite->LoadTexture("../assets/doors.png");
	m_sprite->height = height;
	m_sprite->width = width;
}

void OutDoor::update()
{
}

void OutDoor::OnEvent(InputKey key)
{
}

void OutDoor::PassMessage(std::string message)
{
}
