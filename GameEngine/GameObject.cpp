#include "GameObject.h"
#include "ComponentTypes.h"
#include "Component.h"

int GameObject::sObjectIDCounter = 0;
std::vector<GameObject*> GameObject::EntityList;
GameObject* GameObject::mainPlayer;

GameObject::GameObject() :
	isDead(false),
	m_components(),
	m_id(++sObjectIDCounter)
{
	m_components =  new std::vector<Component*>();
	m_phComponent = nullptr;
	birth = SDL_GetTicks() / 1000;
	m_State = EntityState::Idle;
}

GameObject::~GameObject(void)
{
	/*int endIndex = m_components.size() - 1;
	for (; endIndex >= 0; --endIndex)
	{
		if (m_components[endIndex]->isDead)
		{
			delete m_components[endIndex];
			m_components[endIndex] = m_components[m_components.size() - 1];
			m_components.pop_back();
		}
	}*/
}

void GameObject::update()
{
	int endIndex = m_components->size() - 1;
	for (; endIndex >= 0; --endIndex)
	{
		if ((*m_components)[endIndex]->isDead)
		{
			/*delete m_components[endIndex];
			m_components[endIndex] = m_components[m_components.size() - 1];
			m_components.pop_back();*/
		}
		else
		{
			if (m_components->size() != 0/*[endIndex] != NULL*/)
			{
				(*m_components)[endIndex]->update();
				(*m_components)[endIndex]->render();
			}
		}
	}
}


int GameObject::GetID(void) const
{
	return m_id;
}

void GameObject::AddComponent(Component *pComponent)
{
	//Make sure this component doesn't already exist
	//Component *pComponent = pComp;
	VecItor found = std::find(m_components->begin(), m_components->end(), pComponent);
	if (found != m_components->end())
		return;


	//Set this object as the parent
	pComponent->SetParent(this);
	m_components->push_back(pComponent);
	pComponent->init();
}

void GameObject::RemoveComponent(Component* pToRemove)
{
	//Make the sure the instance exists in this object
	VecItor end = m_components->end();
	VecItor itor = std::find(m_components->begin(),m_components->end(), pToRemove);

	if (itor != end)
 		(*itor)->isDead = true;//return;

	//(*itor)->isDead = true;
}

void GameObject::createBody(int x, int y, int w, int h, GameObject* gb,bool dynamicObj)
{
	if (!m_phComponent)
		m_phComponent = new PhysicsComponent();
	 m_phComponent->createBody(x,y,w,h, gb,dynamicObj);
}

ObjectTypes GameObject::GetType(void) const
{
	return m_type;
}

void GameObject::SetType(enum ObjectTypes objType)
{
	m_type = objType;
}

b2Vec2 GameObject::GetBodyPositions()
{
	return m_phComponent->GetBodyPositions();
}

void GameObject::setAwake(bool state)
{
	m_phComponent->GetBody()->SetAwake(state);
}

void GameObject::setTransform(b2Vec2 positions, float angle)
{
	m_phComponent->GetBody()->SetTransform(positions, angle);
}

void GameObject::removeObject(GameObject *gobj)
{
	std::vector<GameObject*>::iterator objItr = GameObject::EntityList.begin();
	while (objItr != GameObject::EntityList.end())
	{
		if ((*objItr)->GetID() == gobj->GetID())
		{
			//ManageGameObjects::Get().removeObject(*objItr);
			GameObject::EntityList.erase(objItr);
			
			break;
		}
		else
			objItr++;
	}
}

Component * GameObject::GetComponent(enum ComponentTypes type)
{
	size_t size = m_components->size();
	for (size_t i = 0; i < size; ++i)
	{
		//if we found the correct type, return it
		if ((*m_components)[i]->GetType() == type)
		{
			return(*m_components)[i];
		}
	}

	return nullptr;
}
