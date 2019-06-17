#include "GravityComponent.h"
#include "GameObject.h"
#include <iostream>

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

	
	std::cout << abs(gameObject->velocity.z) << std::endl;

	gameObject->velocity = gameObject->velocity + vectemp;
}

