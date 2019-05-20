#pragma once

#include "DrawComponent.h"
#include "ObjModel.h"

class BallComponent : public DrawComponent
{
private:
	ObjModel* ball;
	float speed;
public:
	BallComponent();
	~BallComponent();

	virtual void draw() override;
	void update();
};
