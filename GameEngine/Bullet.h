#pragma once
//#ifndef _BULLET_H
//#define _BULLET_H

#define Bullet_No 6 // Maximum no of alive bullet

#include "GameObject.h"
#include "SDL2-2.0.8\SDL.h"
#include "Listener.h"
#include "SpriteComponent.h"
#include "PhysicsComponent.h"
#include "InputManager.h"
#include "InputKey.h"
#include "Event.h"
#include <math.h>
//#include "Player.h"

class ManageBulletObjects;

class Bullet : public GameObject, public Listener
{
public:
	Bullet();
	~Bullet();

	void Init(b2Vec2 vec);
	void update();
	void render();
	void FireBullet();

	virtual void OnEvent(InputKey key/*const Event &e*/);
	virtual void PassMessage(std::string str);

	void SetPosition(b2Vec2 PlayerPos);
	bool CheckIfOutOfScope(Bullet*);

	bool alive = false;
	bool Destroy = false;

	SDL_RendererFlip GetPlayerFaceDirection();

	static std::vector<Bullet*> bulletList;
	static std::vector<b2Body*> deleteBodies;
	std::vector<Bullet*>::iterator bulletItr;
	void addBullet(Bullet*, b2Vec2 pos);
private:

	SpriteComponent *m_sprite;
	PhysicsComponent *m_physics;
	SDL_Rect b;
	char w, h;
	int MouseXpos, MouseYpos;
	float angleX, angleY;
	
	b2Vec2 vecPos, dirVec;
	b2Body* DeleteBody;

	void RemoveBullet();
	void CheckBeforeDraw();
	void DeleteBodiesIfAny();
}/*bullet[Bullet_No]*/;


//#endif