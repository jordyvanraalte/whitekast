#include "LineColliderComponent.h"
#include "GameObject.h"

LineCollideComponent::LineCollideComponent(GameObject* gameobject)
{
	this->gameObject = gameobject;
	hitbox = new LinesHitbox(gameObject->coordinates, gameObject->scale);
}

LineCollideComponent::~LineCollideComponent()
= default;

Hitbox* LineCollideComponent::getHitbox()
{
	return hitbox;
}

void LineCollideComponent::update(float elapsedTime)
{
	hitbox->shiftColliders(gameObject->position);
}
