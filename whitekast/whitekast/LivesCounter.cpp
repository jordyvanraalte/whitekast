#include "LivesCounter.h"

static LivesCounter* livesCounterInstance;

LivesCounter::LivesCounter()
{
	lives = 3;
}

LivesCounter::~LivesCounter()
{

}

void LivesCounter::loseLive()
{
	lives -= 1;
}


void LivesCounter::resetLives()
{
	lives = 3;
}
int LivesCounter::getLives()
{
	return lives;
}

void LivesCounter::setLives(int lives)
{
	this->lives = lives;
}

LivesCounter* LivesCounter::getInstance()
{
	if (livesCounterInstance == nullptr)
		livesCounterInstance = new LivesCounter();

	return livesCounterInstance;
}
