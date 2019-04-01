#include "GameOverState.h"
#include "MenuState.h"

GameOverState GameOverState::m_GameOverState;
void GameOverState::Init()
{
	SDL_Surface* temp = IMG_Load("../assets/GameOver.png");
	bgTexture = SDL_CreateTextureFromSurface(renderer, temp);
	if (bgTexture == NULL)
		printf("Texture load failed");
	SDL_FreeSurface(temp);
}

void GameOverState::Cleanup()
{
}

void GameOverState::Pause()
{
}

void GameOverState::Resume()
{
}

void GameOverState::HandleEvents(GameStateManager * game)
{
	gamePtr = game;
	InputManager::Get()->update();
	InputKey key = InputManager::Get()->GetPressedKey();
	switch (key)
	{
	case KEYBOARD_KEY_ESCAPE:
		gamePtr->Quit();
		break;
	case KEYBOARD_KEY_SPACE :
		gamePtr->ChangeState(MenuState::Instance());
		break;
	}
}

void GameOverState::Update(GameStateManager * game)
{
	if ((SDL_GetTicks()) > 50000 )
	{
		cout << endl << "Exiting" << endl;
		gamePtr->Quit();
	}
}

void GameOverState::render(GameStateManager * game)
{
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, bgTexture, NULL, NULL);
	SDL_RenderPresent(renderer);
}
