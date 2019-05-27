#pragma once
#include "State.h"
class StateManager
{
public:
	~StateManager();

	
	void setState(State* state);
	State* getState();
	void handle();
	static StateManager* getInstance();
private:
	State* state;

	StateManager();
};

