#include "IntroState.h"
#include "MenuState.h"

IntroState IntroState::m_IntroState;

void IntroState::Init()
{
	SDL_Surface* temp = IMG_Load("../assets/LoadingScreen.png");
	bgTexture = SDL_CreateTextureFromSurface(renderer, temp);
	if (bgTexture == NULL)
		printf("Texture load failed");
	SDL_FreeSurface(temp);

	printf("IntroState Init\n");

	InputManager::Get()->AddCommand(SDLK_SPACE, KEYBOARD_KEY_SPACE);
	InputManager::Get()->AddCommand(SDLK_ESCAPE, KEYBOARD_KEY_ESCAPE);
}

void IntroState::Cleanup()
{
	printf("IntroState Cleanup\n");
}

void IntroState::Pause()
{
	printf("IntroState Pause\n");
}

void IntroState::Resume()
{
	printf("IntroState Resume\n");
}

void IntroState::HandleEvents(GameStateManager *game)
{
	gamePtr = game;
	InputManager::Get()->update();
	InputKey key = InputManager::Get()->GetPressedKey();
	switch (key)
	{
	case KEYBOARD_KEY_SPACE:
		gamePtr->ChangeState(MenuState::Instance());
		break;
	case KEYBOARD_KEY_ESCAPE:
		gamePtr->Quit();
		break;
	}
}

void IntroState::Update(GameStateManager * game)
{

}

void IntroState::render(GameStateManager * game)
{
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, bgTexture, NULL, NULL);
	SDL_RenderPresent(renderer);
}