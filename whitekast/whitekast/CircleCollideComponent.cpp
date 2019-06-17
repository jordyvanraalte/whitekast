#include "CircleCollideComponent.h"
#include "GameObject.h"

CircleCollideComponent::CircleCollideComponent(GameObject* gameobject)
{
	this->gameObject = gameobject;
	hitbox = new CircleHitbox(gameObject->position, gameObject->model->diameter, gameobject->scale);
}

CircleCollideComponent::~CircleCollideComponent() = default;

Hitbox* CircleCollideComponent::getHitbox()
{
	return hitbox;
}

Hitbox* CircleCollideComponent::getCirclebox()
{
	return hitbox;
}

void CircleCollideComponent::drawHitbox()
{
	hitbox->drawColliders();
}

void CircleCollideComponent::update(float elapsedTime)
{
	hitbox->shiftColliders(gameObject->position);
}
