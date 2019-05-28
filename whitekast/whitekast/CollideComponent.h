#pragma once
#include "Component.h"
#include "HitBox.h"

class CollideComponent : public Component
{

protected:

	Hitbox* hitbox;

public:

	CollideComponent();
	~CollideComponent();

	virtual Hitbox* getHitbox() = 0;

};

