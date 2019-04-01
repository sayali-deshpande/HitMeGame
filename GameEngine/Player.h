#pragma once
//#ifndef _PLAYER_H
//#define _PLAYER_H

#include "GameObject.h"
#include "PhysicsComponent.h"
#include "SpriteComponent.h"
#include "Animation.h"
#include "Event.h"
#include "Listener.h"
#include "InputManager.h"
#include "Bullet.h"

class Player : public GameObject, public Listener
{
public:
	Player();
	~Player();

	void Init();
	void update();
	void render();

	void Play(const char* animName);
	void HandleInput(SDL_Event *e);

	virtual void OnEvent(InputKey key/*const Event &e*/); //overridden function
	virtual void PassMessage(std::string message); //overridden function

	b2Vec2 GetPlayerPosition();
	void deletePlayer();
private:
	SpriteComponent *spriteComponent; 
	PhysicsComponent *physicsComponent; 

	std::map<const char*, Animation> animations;

	int m_frames;
	int m_speed;
	int animIndex = 0;
	bool walk = false;
};

//#endif