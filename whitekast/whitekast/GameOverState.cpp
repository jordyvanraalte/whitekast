#include "GameOverState.h"



GameOverState::GameOverState()
{
}


GameOverState::~GameOverState()
{
}

void GameOverState::handle(Game* game)
{
	game->reset();
}


