#pragma once
#include "State.h"

class PauseState : public State
{
public:
	PauseState();
	~PauseState();
	void handle() override;
};

