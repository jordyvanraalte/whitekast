#pragma once
#include "State.h"


class HomeState : public State
{
public:
	HomeState();
	~HomeState();
	void handle(Game* game) override;
};

