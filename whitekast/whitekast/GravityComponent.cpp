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
	Vec3f vectemp = gravity;
	vectemp.applyTime(elapsedTime);
	gameObject->velocity = gameObject->velocity + vectemp;
}

