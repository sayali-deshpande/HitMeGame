#ifndef _POSITIONCOMPONENT_H
#define _POSITIONCOMPONENT_H
#include "Component.h"
#include "ComponentTypes.h"
#include "MathHelper.h"
#include "Box2D\Box2D.h"

using namespace std;
class PositionComponent : public Component
{
public:
	Vector2 m_position;
	Vector2 m_velocity;

	int speed = 1;
	PositionComponent(float x = 0.0f, float y = 0.0f) : Component(CT_PositionComponent)
	{
		m_position.x = x;
		m_position.y = y;
	}

	void init() override
	{
		m_velocity.x = 0;
		m_velocity.y = 0;
	}
	void update() override
	{
		//m_position.Subtract(Vector2(0, -1));
		m_position.x = (m_position.x + m_velocity.x) * speed;
		m_position.y = (m_position.y + m_velocity.y) * speed;
	}
	void render() override
	{

	}

	b2Body* CreateDynamicBody();
	
};

#endif