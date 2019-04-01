#include "MenuState.h"
#include "PlayState.h"

MenuState MenuState::m_MenuState;
void MenuState::Init()
{
	bg = SDL_GetWindowSurface(g_window);
	
	SDL_Surface* temp = IMG_Load("../assets/MenuBg.png");
	bgTexture = SDL_CreateTextureFromSurface(renderer, temp);
	if (bgTexture == NULL)
		printf("Texture load failed");
	SDL_FreeSurface(temp);

	SDL_Surface* temp1 = IMG_Load("../assets/PlayButton.png");
	playButton = SDL_CreateTextureFromSurface(renderer, temp1);
	if (bgTexture == NULL)
		printf("Texture load failed");
	SDL_FreeSurface(temp1);
	playRect.x = 300;
	playRect.y = 400;
	playRect.w = 400;
	playRect.h = 100;
	
	SDL_Surface* temp2 = IMG_Load("../assets/ExitButton.png");
	exitButton = SDL_CreateTextureFromSurface(renderer, temp2);
	if (bgTexture == NULL)
		printf("Texture load failed");
	SDL_FreeSurface(temp2);
	exitRect.x = 300 ;
	exitRect.y = 600 ;
	exitRect.w = 400;
	exitRect.h = 100;

	InputManager::Get()->AddCommand(SDL_MOUSEMOTION, MOUSEBUTTONDOWN);
}

void MenuState::Cleanup()
{
}

void MenuState::Pause()
{
}

void MenuState::Resume()
{
}

void MenuState::HandleEvents(GameStateManager * game)
{
	gamePtr = game;
	InputManager::Get()->update();
	InputKey key = InputManager::Get()->GetPressedKey();

	switch (key)
	{
		case MOUSEBUTTONDOWN:
		{
			float x = InputManager::Get()->getMouseX();
			float y = InputManager::Get()->getMouseY();

			if (x >= playRect.x && x <= playRect.x + playRect.w && y >= playRect.y && y <= playRect.y + playRect.h)
				playBtnPressed = true;
			if (x >= exitRect.x && x <= exitRect.x + exitRect.w && y >= exitRect.y && y <= exitRect.y + exitRect.h)
				exitBtnPressed = true;
		}
		break;
	}
	if (playBtnPressed)
	{
		game->ChangeState(PlayState::Instance());
		printf("\n Play button pressed..");
		playBtnPressed = false;
	}
	if (exitBtnPressed)
	{
		exitBtnPressed = false;
		game->Quit();
	}
}

void MenuState::Update(GameStateManager * game)
{
}

void MenuState::render(GameStateManager * game)
{
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, bgTexture, NULL, NULL);
	SDL_RenderCopy(renderer, playButton, NULL, &playRect);
	SDL_RenderCopy(renderer, exitButton, NULL, &exitRect);
	SDL_RenderPresent(renderer);
}