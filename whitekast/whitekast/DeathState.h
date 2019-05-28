#pragma once
#include "State.h"
#include "PlayState.h"
#include "StateManager.h"
#include "Game.h"

class DeathState : public State
{
public:
	DeathState();
	~DeathState();
	void handle(Game* game) override;
};

