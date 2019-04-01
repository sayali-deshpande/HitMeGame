#pragma once

#include "SDL2-2.0.8\SDL.h"
#include <iostream>
#include <vector>
#include "GlobalDeclarations.h"
#include "InputManager.h"

class GameState;

class GameStateManager
{
public:
	void Init(const char* title, int width = 640, int height = 480,
		int bpp = 0, bool fullscreen = false);
	void Cleanup();

	void ChangeState(GameState* state);
	void PushState(GameState* state);
	void PopState();

	void HandleEvents();
	void Update();
	void render();

	bool Running() { return m_running; }
	void Quit() { m_running = false; }

	SDL_Surface* screen;
	SDL_sem* gThread = nullptr;

private:
	// the stack of states
	std::vector<GameState*> states;

	bool m_running;
	bool m_fullscreen;

};