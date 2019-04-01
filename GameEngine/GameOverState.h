#pragma once
#include "GameState.h"
#include "GlobalDeclarations.h"
#include "InputManager.h"
#include "SDL2-2.0.8\SDL.h"
#include "SDL2-2.0.8\SDL_image.h"

class GameOverState : public GameState
{
public:
	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(GameStateManager *game);
	void Update(GameStateManager *game);
	void render(GameStateManager *game);

	static GameOverState* Instance() {
		return &m_GameOverState;
	}

protected:
	GameOverState() {}
private:
	static GameOverState m_GameOverState;

	SDL_Texture *bgTexture;
	GameStateManager *gamePtr;
};