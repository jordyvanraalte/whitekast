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
	virtual void drawWithTextures() override;
	void update();
};
