#include "GravityComponent.h"
#include "GameObject.h"

GravityComponent::GravityComponent(Vec3f g)
{
	gravity = g;
}

GravityComponent::~GravityComponent()
= default;

void GravityComponent::update(const float elapsedTime)
{
	gravity.applyTime(elapsedTime);
	gameObject->velocity = gameObject->velocity - gravity;
}

