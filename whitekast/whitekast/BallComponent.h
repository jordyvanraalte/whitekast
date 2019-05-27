#pragma once

#include "DrawComponent.h"
#include "ObjModel.h"


struct Circle
{
	float x;
	float y;
	float radius;
};

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
