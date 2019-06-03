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

bool FlipComponent::isUp() const
{
	return up;
}

void FlipComponent::setUp(const bool up)
{
	this->up = up;
}

void FlipComponent::handleEvent(float elapsedTime)
{
	if (flipping)
	{
		if (up)
		{
			gameObject->rotation.y += elapsedTime * speed;
		}
		else
		{
			gameObject->rotation.y -= elapsedTime * speed;
		}

		if (gameObject->rotation.y >= 45)
		{
			up = false;
		}
		else if (gameObject->rotation.y < 0)
		{
			up = true;
			flipping = false;
			gameObject->rotation.y = 0;
		}
	}
}

void FlipComponent::setHandle(bool handle)
{
	this->flipping = handle;
}
