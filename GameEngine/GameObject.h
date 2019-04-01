//#ifndef _GAMEOBJECT_H
//#define _GAMEOBJECT_H
#pragma once

#include "ComponentTypes.h"
#include "PhysicsComponent.h"
#include <vector>
#include "Box2D\Box2D.h"
#include <unordered_map>
#include <iostream>

class Component;

class EntityLife {
public:
	int Health = 100;
};

enum EntityState{
	Idle = 0, WalkLeft = 1, WalkRight = 2,  GoUp = 5, GoDown = 6, Jump = 4, Attacking = 7, Recovery = 8, Chasing = 9, Death = 10
};

class GameObject
{
public:
	GameObject(/*const std::string& str*/);
	~GameObject();

	void Init();
	void update();
	void AddComponent(Component *pcomp);
	void RemoveComponent(Component *comp);
	void createBody(int x, int y, int w, int h, GameObject* gb,bool dyn);

	int GetID(void) const;
	enum ObjectTypes GetType(void) const;

	Component * GetComponent(enum ComponentTypes type);
	bool         isDead;      //!< flag to control when a game object should be destroyed
	void SetType(enum ObjectTypes type);

	//Functions related to physics Component
	b2Vec2  GetBodyPositions();
	void setAwake(bool state);
	void setTransform(b2Vec2 positions, float angle);
	b2BodyType GetBodyType() { return m_phComponent->GetBody()->GetType(); }
	b2Body* GetBody() { return m_phComponent->GetBody(); }
	SDL_Texture        *tex;

	EntityLife Life;
	void SetState(EntityState newState) { m_State = newState; }
	EntityState GetCurrentState() { return m_State; }

	static std::vector<GameObject*> EntityList;
	static GameObject* mainPlayer;
	void removeObject(GameObject *gobj);
private:
	
	typedef std::vector<Component*> ComponentVec; //!< Typedef for my Vector of Components
	typedef ComponentVec::iterator VecItor;         //!< Typedef for my container iterator
													//container to hold physics objects associated with game object
	typedef std::unordered_map<std::string, b2Body*> BodyMap;
	typedef BodyMap::iterator BodyMapItr;
	BodyMap m_bodyMap;

	ComponentVec		 *m_components;                      //!< Vector of Components to Update
	enum ObjectTypes m_type;                            //!< The ArcheType of the Game Object
	const int			 m_id;                              //!< Unique ID of the Game Object
	static int			 sObjectIDCounter;                 //!< Shared ID counter for all Game Objects 
	PhysicsComponent*	m_phComponent;
	bool				DrawOnce = false;
	
  //Variables related to Players in Game
	uint32 birth = 0;
	float tick = 0;
	float recoveryIndex = 0.0f;
	float lastAttack = 0.0f;
	float attackRecovery = 0.5f;

	EntityState m_State;

};

class ManageGameObjects
{
private:
	std::vector<GameObject*> gObjects;
public:
	int getSize()
	{
		return gObjects.size();
	}
	void update()
	{
		for (auto& obj : gObjects)
				obj->update();
	}

	void addObject(GameObject *gobj)
	{
		gObjects.push_back(gobj);
	}

	void removeObject(GameObject *gobj)
	{
		std::vector<GameObject*>::iterator objItr  = gObjects.begin();
		while (objItr!= gObjects.end())
		{
			if ((*objItr)->GetID() == gobj->GetID())
			{
				gObjects.erase(objItr);
				break;
			}
			else
			objItr++;
		}
	}

	int findElement(GameObject* obj)
	{
		if (std::find(gObjects.begin(), gObjects.end(), obj) != gObjects.end())
			return true;
		else
			return false;
	}

	void timepass() {
		std::vector<GameObject*>::iterator objItr = gObjects.begin();
		while (objItr != gObjects.end())
		{
			if((*objItr)->isDead)
				std::cout<<std::endl<<"I am dead";
		}
	}
};


//#endif
