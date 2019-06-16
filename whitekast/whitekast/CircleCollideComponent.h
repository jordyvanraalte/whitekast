#pragma once
#include "HitBox.h"
#include "CollideComponent.h"

class CircleCollideComponent : public CollideComponent
{
	Hitbox* hitbox;
public:
	CircleCollideComponent(GameObject *gameobject);
	~CircleCollideComponent();

	Hitbox* getHitbox() override;
	Hitbox* getCirclebox() override;

	void update(float elapsedTime) override;
};

