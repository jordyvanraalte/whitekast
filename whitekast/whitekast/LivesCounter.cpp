#include "LivesCounter.h"

static LivesCounter* instance;

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
	if (instance == nullptr)
		instance = new LivesCounter();

	return instance;
}
