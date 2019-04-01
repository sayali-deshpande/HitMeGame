#pragma once
//#ifndef _PACMAN_H
//#define _PACMAN_H

#include "GameObject.h"
#include "SpriteComponent.h"
#include "PhysicsComponent.h"
#include "Listener.h"
#include "GlobalDeclarations.h"
#include "InputManager.h"
#include <cstdlib>
#include <ctime>
#include "BroadCaster.h"

class PacMan : public GameObject, public Listener
{
private:
	SpriteComponent *m_sprite;
	PhysicsComponent *m_physics;

	SDL_RendererFlip FaceDirection;

	bool visible = false;
	bool hit = false;
	bool changeDirection;
	int xPos, yPos;
	int previousRandomNum;

	//Variables related to Players in Game
	uint32 birth = 0;
	float tick = 0;
	float recoveryIndex = 0.0f;
	float lastAttack = 0.0f;
	float attackRecovery = 0.5f;

	bool isAtLeftBoundry();
	bool isAtRightBoundry();
	bool isAtUpBoundry();
	bool isAtBottomBoundry();

	void GetRandomDirection();
public:

	PacMan();
	~PacMan();

	void Init();
	void update();
	void render();
	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();

	virtual void OnEvent(InputKey key/*const Event &e*/); //overridden function
	virtual void PassMessage(std::string message); //overridden function

	void collisionCallback(GameObject *obj);

	float GetPacManXpos();
	float GetPacManYpos();
};


//#endif