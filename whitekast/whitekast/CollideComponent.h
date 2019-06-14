#pragma once
#include "HitBox.h"
#include "Component.h"

class Component;
class CollideComponent : virtual public Component
{
public:

	CollideComponent();
	~CollideComponent();

	virtual Hitbox* getHitbox() = 0;

};

