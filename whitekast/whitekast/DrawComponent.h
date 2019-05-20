#pragma once

#include "Component.h"

class DrawComponent : public Component
{
public:
	DrawComponent();
	~DrawComponent();
	virtual void draw() = 0;
	virtual void drawWithTextures() = 0;
};

