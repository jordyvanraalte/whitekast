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
	virtual Hitbox* getCirclebox() = 0;

	virtual void drawHitbox() = 0;

	virtual void flipHitbox(float x, float y) {};

};

