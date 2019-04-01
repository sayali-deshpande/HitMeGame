#include "GameStateManager.h"
#include "IntroState.h"
#include <time.h>

int main(int argc, char*argv[])
{
	srand(time(0));
	GameStateManager game;
	game.Init("Shoot Me!");
	
	//load the intro
	game.ChangeState(IntroState::Instance());

	//main loop
	while (game.Running())
	{
		game.HandleEvents();
		game.Update();
		game.render();
	}

	//cleanup the engine
	game.Cleanup();
	return 0;
}

