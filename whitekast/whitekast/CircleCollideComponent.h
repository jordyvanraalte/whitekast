#pragma once
#include "CollideComponent.h"

class CircleCollideComponent : public CollideComponent
{
public:
	CircleCollideComponent();
	~CircleCollideComponent();

	Hitbox* getHitbox() override;
};

