#pragma once
#include "GameState.h"
#include "GlobalDeclarations.h"
#include "InputManager.h"
#include "SDL2-2.0.8\SDL.h"
#include "SDL2-2.0.8\SDL_image.h"
#include "SDL2-2.0.8\SDL_ttf.h"
#include "Component.h"
#include "ComponentTypes.h"
#include "GameObject.h"
#include "PositionCompponent.h"
#include "SpriteComponent.h"
#include "PhysicsComponent.h"
#include "LabelComponent.h"
#include "InputManager.h"
#include "Box2D\Box2D.h"
#include "Player.h"
#include "BroadCaster.h"
#include "Bullet.h"
#include "PacMan.h"
#include "GroundObjects.h"
#include "OutDoor.h"
#include "Diamond.h"
#include "SpawnManager.h"
#include <sstream>

class PlayState : public GameState
{
public:
	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(GameStateManager *game);
	void Update(GameStateManager *game);
	void render(GameStateManager *game);

	static PlayState* Instance() {
		return &m_PlayState;
	}

	void ManageMobPool();
	void updateObjectList();
	void InitSpawnManager();
	void getDeltaTime();

	SpawnManager spawn_manager;
	//ManageGameObjects manageObjects;
	SpriteComponent* m_sComponent;
	PhysicsComponent* m_phyComponent;
	static SDL_Event s_Events;

	static int NoOfEnemyDied;
protected:
	PlayState() {}
private:
	static PlayState m_PlayState;
	ManageGameObjects manageObjects;

	SDL_Surface *bg = NULL;
	GameStateManager *gamePtr;
	//GameObjects
	Player *player;
	Bullet *bullet = NULL;
	PacMan *pacMan = NULL;

	void LoadGroundObjects();
	void LoadInputCommands();

	//Timer related variables
	unsigned int m_CurrTime;
	unsigned int m_ElapsedTime;
	float m_DeltaTime;
	float m_TimeScale;
	float timeStep = 1.0f / 60.0f;
	Uint32 tick;

	TTF_Font *font;


	LabelComponent* textToDisplay;
};