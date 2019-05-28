#include "FlipComponent.h"
#include "GameObject.h"
#include <GL/freeglut.h>


FlipComponent::FlipComponent()
{
}

FlipComponent::~FlipComponent()
{
}

bool FlipComponent::isFlipping() const 
{
	return flipping;
}

void FlipComponent::setFlipping(const bool flipping)
{
	this->flipping = flipping;
}

void FlipComponent::handleEvent(float elapsedTime)
{
	if (flipping)
	{
		gameObject->rotation.y += elapsedTime * speed;
	}
	else
	{
		gameObject->rotation.y -= elapsedTime * speed;
	}

	if (gameObject->rotation.y >= 45)
		flipping = false;
}

