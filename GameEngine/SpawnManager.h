#pragma once
//#ifndef _SPAWNMANAGER_H
//#define _SPAWNMANAGER_H

#include <map>
#include <vector>
#include "SDL2-2.0.8\SDL.h"
#include <iostream>

#include "GameObject.h"
#include "GlobalDeclarations.h"

#include "BroadCaster.h"
#include "PacMan.h"

class SpawnManager
{
private:

	Uint32 lastSpawn = 0;
	int32 lastSpawnIndex = 0;
	size_t SpawnEvery = 5;

	SDL_Rect spawnPoints[10] = { {0,0,0,0} };

	size_t maxSpawn = 3;
	static int PacManCount;
public:

	std::map<std::string, PacMan>* MobList;
	std::vector<PacMan*> spawned;

	void ManagePool(Uint32 tick);
	bool overridebusy = false;
	void SpawnMob();
	bool overridespawn;
};
//#endif
