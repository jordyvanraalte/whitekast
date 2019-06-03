#include "CircleCollideComponent.h"
#include "GameObject.h"

CircleCollideComponent::CircleCollideComponent(GameObject* gameobject)
{
	this->gameObject = gameobject;
	hitbox = new CircleHitbox(gameObject->position, gameObject->model->diameter);
}

CircleCollideComponent::~CircleCollideComponent() = default;

Hitbox* CircleCollideComponent::getHitbox()
{
	return hitbox;
}

void CircleCollideComponent::update(float elapsedTime)
{
	hitbox->shiftColliders(gameObject->position);
}
