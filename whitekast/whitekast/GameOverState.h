#pragma once
#include "Game.h"
#include "HomeState.h"
#include "State.h"


class GameOverState : public State
{
public:
	GameOverState();
	~GameOverState();
	void handle(Game* game) override;
};

