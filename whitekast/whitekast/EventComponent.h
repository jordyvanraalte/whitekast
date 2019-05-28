#pragma once
#include "Component.h"

class EventComponent : public Component
{
public:
	EventComponent();
	~EventComponent();
	virtual void handleEvent() = 0;
};

