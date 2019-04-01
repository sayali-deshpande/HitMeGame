#include "PhysicsComponent.h"
#include "Box2D\Box2D.h"
#include "GlobalDeclarations.h"

PhysicsComponent::~PhysicsComponent()
{
}

void PhysicsComponent::init()
{
	world->SetGravity(b2Vec2(0.0f, -9.8f));
	timeStep = 1.0f / FRAME_RATE;
	m_velocityIterator = 4;
	m_positionIterator = 4;
	world->SetAllowSleeping(true);
	world->SetContinuousPhysics(true);
	world->SetContactListener(&collisionlistener);
	height = width = 0.0f;
	//m_body = NULL;
}

void PhysicsComponent::ReSetGravity(float x, float y)
{
	world->SetGravity(b2Vec2(x, y));
}

void PhysicsComponent::createBody(int x, int y, int w, int h, GameObject* gb, bool dyn )
{
	b2BodyDef bodydef;
	if (dyn)
		bodydef.type = b2_dynamicBody;
	else
		bodydef.type = b2_staticBody;

	float xPos, yPos;

	xPos = x + (w / 2);
	yPos = y + (h / 2);
	xPos = xPos *  0.02;
	yPos = yPos *  -0.02;


	bodydef.position.Set(xPos,yPos);
	bodydef.awake = false;
	bodydef.bullet = true;
	bodydef.userData = &gb;

	m_body = world->CreateBody(&bodydef);
	
	b2PolygonShape shape;	
	height =  (h / 2) / meterToPixel;
	width =  (w / 2) / meterToPixel;
	shape.SetAsBox(width , height);

	b2FixtureDef fixturedef;
	fixturedef.shape = &shape;
	fixturedef.density = 1.0;
	if (!dyn)
		fixturedef.isSensor = false;
	fixturedef.friction = 0.3f;
	m_body->CreateFixture(&fixturedef);
	//m_body->SetUserData(this);
	m_body->SetGravityScale(0.01f);
}

b2Vec2 PhysicsComponent::GetBodyPositions()
{
	return m_body->GetPosition();
}

b2Body * PhysicsComponent::GetBody()
{
	return m_body;
}

void PhysicsComponent::update()
{
	world->Step(timeStep, m_velocityIterator, m_positionIterator);
	
}

void PhysicsComponent::render()
{
}
