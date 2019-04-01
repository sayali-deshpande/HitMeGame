#pragma once
#include "GameState.h"
#include "GlobalDeclarations.h"
#include "InputManager.h"
#include "SDL2-2.0.8\SDL.h"
#include "SDL2-2.0.8\SDL_image.h"
#include "SDL2-2.0.8\SDL_ttf.h"

class MenuState : public GameState
{
public:
	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(GameStateManager *game);
	void Update(GameStateManager *game);
	void render(GameStateManager *game);

	static MenuState* Instance() {
		return &m_MenuState;
	}

protected:
	MenuState() {}
private:
	static MenuState m_MenuState;

	SDL_Surface *bg = NULL;
	SDL_Texture *bgTexture,*playButton, *exitButton;
	SDL_Rect playRect, exitRect;
	GameStateManager *gamePtr;
	bool playBtnPressed, exitBtnPressed;
};