#include "CircleCollideComponent.h"
#include "GameObject.h"

CircleCollideComponent::CircleCollideComponent()
{
	hitbox = new CircleHitbox(gameObject->position, gameObject->objModel->radius);
}

CircleCollideComponent::~CircleCollideComponent()
= default;

Hitbox* CircleCollideComponent::getHitbox()
{
	return hitbox;
}
