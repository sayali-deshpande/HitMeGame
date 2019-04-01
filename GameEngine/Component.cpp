#include "Component.h"

int Component::sComponentID = 0;
Component::Component(enum ComponentTypes type) :
	isDead(false),
	m_obj(0),
	m_type(type),
	m_id(++sComponentID)
{
}

Component::Component()
{
	/*m_id = 0;
	m_type = CT_COMPONENT_MAX;*/
}

Component::~Component()
{
	printf("In Component");
}

void Component::SetParent(GameObject* obj)
{
	m_obj = obj;
}

GameObject* Component::GetParent()
{
	return m_obj;
}
enum ComponentTypes Component::GetType(void) const
{
	return m_type;
}

int Component::GetID(void)const
{
	return m_id;
}