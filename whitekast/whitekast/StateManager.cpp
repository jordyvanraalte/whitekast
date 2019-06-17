#include "StateManager.h"
#include "HomeState.h"

static StateManager* stateManager;
StateManager::StateManager()
{
	state = new HomeState();
}

StateManager::~StateManager()
{
	delete stateManager;
	delete state;
}

void StateManager::setState(State *state)
{
	delete this->state;
	this->state = nullptr;
	this->state = state;
}


State* StateManager::getState()
{
	return this->state;
}

void StateManager::handle(Game* game)
{
	this->state->handle(game);
}

StateManager* StateManager::getInstance()
{
	if(stateManager == nullptr)
	{
		stateManager = new StateManager();
	}
	return stateManager;
}
