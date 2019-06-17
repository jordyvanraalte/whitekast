#pragma once
#include "CollideComponent.h"

class LineCollideComponent : public CollideComponent
{

	Hitbox* hitbox;
	Hitbox* circle;

public:
	LineCollideComponent(GameObject* gameobject, float wkscale);
	~LineCollideComponent();

	Hitbox* getHitbox() override;
	Hitbox* getCirclebox() override;

	void drawHitbox() override;

	void update(float elapsedTime) override;
	void flipHitbox(float x, float y) override;
};

