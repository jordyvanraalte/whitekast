#pragma once
#include "CollideComponent.h"

class LineCollideComponent : public CollideComponent
{
	Hitbox* hitbox;
public:
	LineCollideComponent(GameObject* gameobject, float wkscale);
	~LineCollideComponent();

	Hitbox* getHitbox() override;
	void update(float elapsedTime) override;
};

