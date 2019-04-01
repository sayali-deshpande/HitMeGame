//#ifndef _COMPONENT_H
//#define _COMPONENT_H
#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
#include "ComponentTypes.h"


class GameObject;
class Component;

class Component
{
public:
	Component(enum ComponentTypes type);
	Component();
	virtual				~Component(void);

	virtual				 void init() {}
	virtual				 void update() {}
	virtual				 void render() {}

	GameObject*			 GetParent();
	void				 SetParent(GameObject* obj);
	int					 GetID(void) const;
	enum ComponentTypes  GetType(void) const;

	bool				isDead;
protected:
	GameObject*			m_obj;
private:
	int			m_id;
	enum ComponentTypes m_type;
	static  int			sComponentID;
};
//#endif