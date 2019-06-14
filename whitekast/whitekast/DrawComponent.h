#pragma once

#include "Component.h"

class Component;
class DrawComponent : virtual public Component
{
public:

	DrawComponent();
	~DrawComponent();
	virtual void draw() = 0;
};
