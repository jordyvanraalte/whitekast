#include "DeathState.h"
#include "GameOverState.h"
#include "LivesCounter.h"
#include "HighScore.h"
#include "PointCounter.h"

DeathState::DeathState()
{
}


DeathState::~DeathState()
{
}

void DeathState::handle(Game* game)
{
	if (LivesCounter::getInstance()->getLives() > 1)
	{
		LivesCounter::getInstance()->loseLive();
		StateManager::getInstance()->setState(new HomeState());
		Game::getInstance()->death();
	}
	else
	{
		HighScore::getInstance()->setHighScore(PointCounter::getInstance()->getPoints());
		Game::getInstance()->reset();
	}
}
