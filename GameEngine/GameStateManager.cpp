#include "GameStateManager.h"
#include "GameState.h"

void GameStateManager::Init(const char * title, int width, int height, int bpp, bool fullscreen)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}

	//screen = SDL_SetV

	//create window
	g_window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	if (g_window == NULL) {
		printf("Window could not be created! SDL_Error:%s\n", SDL_GetError());
	}

	surface = SDL_GetWindowSurface(g_window);

	if (renderer == NULL)
	{
		renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
		SDL_SetRenderDrawColor(renderer, /*105,105,105*/0, 0, 0, 0);
	}

	gThread = SDL_CreateSemaphore(1);
}

void GameStateManager::Cleanup()
{
	// cleanup the all states
	while (!states.empty()) {
		states.back()->Cleanup();
		states.pop_back();
	}

	printf("GameEngine Cleanup\n");

	// shutdown SDL
	SDL_Quit();
}

void GameStateManager::ChangeState(GameState * state)
{
	// cleanup the current state
		if (!states.empty()) {
			states.back()->Cleanup();
			states.pop_back();
		}

	// store and init the new state
	states.push_back(state);
	states.back()->Init();
}

void GameStateManager::PushState(GameState * state)
{
	// pause current state
	if (!states.empty()) {
		states.back()->Pause();
	}

	// store and init the new state
	states.push_back(state);
	states.back()->Init();
}

void GameStateManager::PopState()
{
	// cleanup the current state
	if (!states.empty()) {
		states.back()->Cleanup();
		states.pop_back();
	}

	// resume previous state
	if (!states.empty()) {
		states.back()->Resume();
	}
}

void GameStateManager::HandleEvents()
{
	// let the state handle events
	states.back()->HandleEvents(this);
}

void GameStateManager::Update()
{
	// let the state update the game
	states.back()->Update(this);
}

void GameStateManager::render()
{
	// let the state draw the screen
	states.back()->render(this);
}
