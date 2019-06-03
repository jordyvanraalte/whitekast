#pragma once
#include "CollideComponent.h"

class LineCollideComponent : public CollideComponent
{
public:
	LineCollideComponent(GameObject *gameobject);
	~LineCollideComponent();

	Hitbox* getHitbox() override;
	void update(float elapsedTime) override;
};

