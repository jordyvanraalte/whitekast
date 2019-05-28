#pragma once

#include "HitBox.h"
#include "Component.h"

class Component;
class CollideComponent : virtual public Component
{

protected:

	Hitbox* hitbox;

public:

	CollideComponent();
	~CollideComponent();

	virtual Hitbox* getHitbox() = 0;

};

