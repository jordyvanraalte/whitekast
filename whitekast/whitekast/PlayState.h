#pragma once
#include "State.h"

class PlayState : public State
{
public:
	PlayState();
	~PlayState();
	void handle() override;
};

