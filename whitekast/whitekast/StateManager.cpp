#include "StateManager.h"
#include "HomeState.h"

static StateManager* instance;
StateManager::StateManager()
{
	state = new HomeState();
}

StateManager::~StateManager()
{
}

void StateManager::setState(State *state)
{
	this->state = state;
}

State* StateManager::getState()
{
	return this->state;
}

void StateManager::handle()
{
	this->state->handle();
}

StateManager* StateManager::getInstance()
{
	if(instance == nullptr)
	{
		instance = new StateManager();
	}
	return instance;
}
