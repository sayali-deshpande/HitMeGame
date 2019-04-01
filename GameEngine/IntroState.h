#pragma once
#include "GameState.h"
#include "GlobalDeclarations.h"
#include "InputManager.h"
#include "SDL2-2.0.8\SDL.h"
#include "SDL2-2.0.8\SDL_image.h"


class IntroState :public GameState
{
public:
	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(GameStateManager *game);
	void Update(GameStateManager *game);
	void render(GameStateManager *game);

	static IntroState* Instance() {
		return &m_IntroState;
	}

protected:
	IntroState() {}
private:
	static IntroState m_IntroState;

	SDL_Surface *bg = NULL;
	SDL_Texture *bgTexture;
	GameStateManager *gamePtr;
};