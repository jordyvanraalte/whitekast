#pragma once

#include "DrawComponent.h"

class BallComponent : public DrawComponent
{
	float speed;
public:
	BallComponent();
	~BallComponent();

	virtual void draw() override;
	void update();
};


