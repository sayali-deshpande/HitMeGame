#include "SpawnManager.h"

int SpawnManager::PacManCount = 0;

void SpawnManager::ManagePool(Uint32 tick)
{
	if (this->overridebusy == false)
	{
		this->lastSpawn = (tick / 1000) - lastSpawnIndex;
		if (static_cast<size_t>(this->lastSpawn) > this->SpawnEvery && this->spawned.size() < this->maxSpawn || this->overridebusy)
		{
			this->lastSpawnIndex = (tick / 1000);
			this->SpawnMob();
			this->overridespawn = false;
		}
		else if (this->spawned.size() >= this->maxSpawn)
		{
			this->lastSpawnIndex = (tick / 1000);
		}
	}
}

void SpawnManager::SpawnMob()
{
	try
	{
		PacMan *pcMan = new PacMan(/*this->MobList->at("PacMan")*/);
		pcMan->Init();

		bodyUserData *bud = new bodyUserData();
		bud->bodyType = OT_Enemy;
		bud->id = PacManCount++;
		pcMan->GetBody()->SetUserData(bud);

		this->spawned.insert(this->spawned.end(), pcMan);
		//set the y position
		this->spawned.at(this->spawned.size() - 1)->GetID();
		BroadCaster::Get()->AddListner(pcMan);
		this->lastSpawnIndex = (SDL_GetTicks() / 1000);

	}
	catch (...) {
		std::cout << std::endl << "Failed to spawn a mob";
	}
}
