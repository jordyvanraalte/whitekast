#include "LineColliderComponent.h"
#include "GameObject.h"

LineCollideComponent::LineCollideComponent(GameObject* gameobject, float wkscale)
{
	this->gameObject = gameobject;
	hitbox = new LinesHitbox(gameObject->coordinates, gameObject->scale, wkscale);
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
