#pragma once
#include "State.h"
#include "Game.h"

class StateManager
{
public:
	~StateManager();
	
	void setState(State* state);
	State* getState();
	void handle(Game* game);
	static StateManager* getInstance();
private:
	State* state;

	StateManager();
};

