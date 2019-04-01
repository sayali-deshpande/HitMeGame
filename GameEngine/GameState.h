#pragma once

#include "GameStateManager.h"

class GameState
{
public:
public:
	virtual void Init() = 0;
	virtual void Cleanup() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void HandleEvents(GameStateManager* game) = 0;
	virtual void Update(GameStateManager* game) = 0;
	virtual void render(GameStateManager* game) = 0;

	void ChangeState(GameStateManager* game, GameState* state) {
		game->ChangeState(state);
	}

protected:
	GameState() { }

};