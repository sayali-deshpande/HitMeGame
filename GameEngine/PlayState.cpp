#include "PlayState.h"
#include "GameOverState.h"

PlayState PlayState::m_PlayState;
int PlayState::NoOfEnemyDied = 0;

void PlayState::Init()
{
	//Create Player 
	player = new Player();
	manageObjects.addObject(player);
	GameObject::EntityList.push_back(player);
	player->SetType(OT_Player);
	player->Init();
	BroadCaster::Get()->AddListner(player);
	GameObject::mainPlayer = player;

	InitSpawnManager();
	//Load the Ground Objects
	LoadGroundObjects();
	LoadInputCommands();

	if (TTF_Init() == -1)
		cout << endl << "Error: Failed to initialise SDL_TTF";

	SDL_Color white = { 255,255,255,255 };

	textToDisplay = new LabelComponent(10, 10, "", "arial", white);
	textToDisplay->AddFont("arial", "../assets/BROADW.ttf", 16);
}

void PlayState::Cleanup()
{
}

void PlayState::Pause()
{
}

void PlayState::Resume()
{
}

void PlayState::HandleEvents(GameStateManager * game)
{
	gamePtr = game;
	InputManager::Get()->update();
	InputKey key = InputManager::Get()->GetPressedKey();
	switch (key)
	{
	case KEYBOARD_KEY_ESCAPE:
		gamePtr->Quit();
		break;
	}
	updateObjectList();

}

void PlayState::Update(GameStateManager * game)
{
	//updateObjectList();
	if ((SDL_GetTicks()) > 20000 && player == NULL)
	{
		cout << endl << "Exiting" << endl;
		gamePtr->ChangeState(GameOverState::Instance());
	}

	getDeltaTime();
	InputManager::Get()->update();

	SDL_RenderClear(renderer);
	ManageMobPool();
	manageObjects.update();
	
	std::stringstream LabelText;
	LabelText << "Player's Score : " << NoOfEnemyDied;
	textToDisplay->SetLabelText(LabelText.str(), "arial");
	//Display text on screen
	textToDisplay->render();
	//SpawnManager
	tick = SDL_GetTicks();
	spawn_manager.ManagePool(tick);
	SDL_RenderPresent(renderer);

	if (m_DeltaTime >= (1.0f / FRAME_RATE))
	{
		/*m_graphics->Render();
		manageObjects.update();
		m_CurrTime = SDL_GetTicks();*/
		if (player)
			player->update();

	}
}

void PlayState::render(GameStateManager * game)
{
}

void PlayState::ManageMobPool()
{
	// Loop through all spawned mobs
	for (size_t i = 0; i < spawn_manager.spawned.size(); i++)
	{
		if (i >= spawn_manager.spawned.size()) {
			break; //just in case?
		}

		//If the entity is dead
		if (this->spawn_manager.spawned[i]->isDead == true) {
			BroadCaster::Get()->RemoveListner(this->spawn_manager.spawned[i]);
			this->spawn_manager.spawned.erase(this->spawn_manager.spawned.begin() + i);

			NoOfEnemyDied++;
			break;
		}
		else {
			if (&spawn_manager.spawned[i]->Life != nullptr) {
				spawn_manager.spawned[i]->update();
				spawn_manager.spawned[i]->render();
				spawn_manager.spawned[i]->isDead = false;
			}
		}
	}
}

void PlayState::updateObjectList()
{
	if (GameObject::EntityList.size() > manageObjects.getSize())
	{
		std::vector<GameObject*>::iterator objItr = GameObject::EntityList.begin();
		int i = 0;
		while (objItr != GameObject::EntityList.end())
		{
			if (!manageObjects.findElement(*objItr))
				manageObjects.addObject(GameObject::EntityList.at(i));
			objItr++;
			i++;
		}
	}

	std::vector<GameObject*>::iterator objItr = GameObject::EntityList.begin();
	int i = 0;
	while (i < GameObject::EntityList.size())
	{
		if ((*objItr)->isDead)
		{
			if (manageObjects.findElement(*objItr))
			{
				if ((*objItr)->GetType() == OT_Player)
				{
					player->deletePlayer();
					delete player;
					player = NULL;
				}
				manageObjects.removeObject(*objItr);
				GameObject::EntityList.erase(GameObject::EntityList.begin() + i);
				break;
			}
		}
		else
			objItr++;
		i++;
	}
}

void PlayState::InitSpawnManager()
{
	//Initialize spawn mob list with list from game
	spawn_manager.MobList = new std::map<std::string, PacMan>;
}

void PlayState::getDeltaTime()
{
	m_ElapsedTime = SDL_GetTicks() - m_CurrTime;
	m_DeltaTime = m_ElapsedTime * 0.001f;
}

void PlayState::LoadGroundObjects()
{
	GroundObjects *GroundObject = new GroundObjects(0, 500, 100, 100);
	GroundObject->init();
	manageObjects.addObject(GroundObject);
	GameObject::EntityList.push_back(GroundObject);

	GroundObjects *GroundObject1 = new GroundObjects(300, 700, 100, 100);
	GroundObject1->init();
	manageObjects.addObject(GroundObject1);
	GameObject::EntityList.push_back(GroundObject1);

	Diamond *d1 = new Diamond(330, 700, 50, 50);
	d1->init();
	manageObjects.addObject(d1);
	GameObject::EntityList.push_back(d1);
	
	/*GroundObjects *GroundObject2 = new GroundObjects(150, 400, 100, 80);
	GroundObject2->init();
	manageObjects.addObject(GroundObject2);
	GameObject::EntityList.push_back(GroundObject2);*/

	/*Diamond *d2 = new Diamond(170, 400, 50, 50);
	d2->init();
	manageObjects.addObject(d2);
	GameObject::EntityList.push_back(d2);*/

	GroundObjects *GroundObject3 = new GroundObjects(400, 300, 100, 80);
	GroundObject3->init();
	manageObjects.addObject(GroundObject3);
	GameObject::EntityList.push_back(GroundObject3);

	Diamond *d3 = new Diamond(420, 300, 50, 50);
	d3->init();
	manageObjects.addObject(d3);
	GameObject::EntityList.push_back(d3);
	
	GroundObjects *GroundObject4 = new GroundObjects(0, 870, 900, 20);
	GroundObject4->init();
	manageObjects.addObject(GroundObject4);
	GameObject::EntityList.push_back(GroundObject4);

	GroundObjects *GroundObject5 = new GroundObjects(0, 990, 1000, 20);
	GroundObject5->init();
	manageObjects.addObject(GroundObject5);
	GameObject::EntityList.push_back(GroundObject5);

	GroundObjects *GroundObject6 = new GroundObjects(700, 500, 100, 80);
	GroundObject6->init();
	manageObjects.addObject(GroundObject6);
	GameObject::EntityList.push_back(GroundObject6);

	Diamond *d4 = new Diamond(720, 500, 50, 50);
	d4->init();
	manageObjects.addObject(d4);
	GameObject::EntityList.push_back(d4);

	GroundObjects *GroundObject7 = new GroundObjects(700, 500, 100, 80);
	GroundObject7->init();
	manageObjects.addObject(GroundObject7);
	GameObject::EntityList.push_back(GroundObject7);

	GroundObjects *GroundObject8 = new GroundObjects(600, 100, 100, 80);
	GroundObject8->init();
	manageObjects.addObject(GroundObject8);
	GameObject::EntityList.push_back(GroundObject8);

	Diamond *d5 = new Diamond(620, 100, 50, 50);
	d5->init();
	manageObjects.addObject(d5);
	GameObject::EntityList.push_back(d5);

	GroundObjects *GroundObject9 = new GroundObjects(100, 100, 100, 80);
	GroundObject9->init();
	manageObjects.addObject(GroundObject9);
	GameObject::EntityList.push_back(GroundObject9);

	Diamond *d6 = new Diamond(120, 100, 50, 50);
	d6->init();
	manageObjects.addObject(d6);
	GameObject::EntityList.push_back(d6);

	GroundObjects *GroundObject10 = new GroundObjects(900, 200, 100, 80);
	GroundObject10->init();
	manageObjects.addObject(GroundObject10);
	GameObject::EntityList.push_back(GroundObject10);

	Diamond *d7 = new Diamond(920, 200, 50, 50);
	d7->init();
	manageObjects.addObject(d7);
	GameObject::EntityList.push_back(d7);

	GroundObjects *GroundObject11 = new GroundObjects(900, 700, 100, 80);
	GroundObject11->init();
	manageObjects.addObject(GroundObject11);
	GameObject::EntityList.push_back(GroundObject11);

	Diamond *d8 = new Diamond(920, 700, 50, 50);
	d8->init();
	manageObjects.addObject(d8);
	GameObject::EntityList.push_back(d8);

	//Load the end door
	OutDoor *end_door = new OutDoor();
	end_door->init();
	manageObjects.addObject(end_door);
	GameObject::EntityList.push_back(end_door);

}

void PlayState::LoadInputCommands()
{
	InputManager::Get()->AddCommand(SDLK_LEFT, KEYBOARD_KEY_LEFT);
	InputManager::Get()->AddCommand(SDLK_RIGHT, KEYBOARD_KEY_RIGHT);
	InputManager::Get()->AddCommand(SDLK_UP, KEYBOARD_KEY_UP);
	InputManager::Get()->AddCommand(SDLK_DOWN, KEYBOARD_KEY_DOWN);
	InputManager::Get()->AddCommand(SDL_KEYDOWN, BUTTON_KEY_DOWN);
	InputManager::Get()->AddCommand(SDL_KEYUP, BUTTON_KEY_UP);
}
