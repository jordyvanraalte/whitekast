#pragma once

#include "DrawComponent.h"

class WorldComponent : public DrawComponent
{
public:
	WorldComponent();
	~WorldComponent();

	virtual void draw() override;
};

