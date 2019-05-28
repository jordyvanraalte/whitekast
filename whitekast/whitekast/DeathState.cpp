#include "DeathState.h"
#include "GameOverState.h"


DeathState::DeathState()
{
}


DeathState::~DeathState()
{
}

void DeathState::handle(Game* game)
{
	if (game->lives > 1)
	{
		game->lives--;
		StateManager::getInstance()->setState(new PlayState());
	}
	else
	{
		StateManager::getInstance()->setState(new GameOverState());
	}
}