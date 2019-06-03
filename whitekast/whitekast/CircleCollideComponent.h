#pragma once
#include "CollideComponent.h"

class CircleCollideComponent : public CollideComponent
{
public:
	CircleCollideComponent(GameObject *gameobject);
	~CircleCollideComponent();
	Hitbox* getHitbox() override;
	void update(float elapsedTime) override;
};

