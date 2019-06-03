#include "FlipComponent.h"
#include "GameObject.h"
#include <GL/freeglut.h>

FlipComponent::FlipComponent(const bool l)
{
	left = l;
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

bool FlipComponent::isLeft() const
{
	return left;
}

void FlipComponent::setUp(const bool up)
{
	this->up = up;
}

void FlipComponent::handleEvent(float elapsedTime)
{
	if (left)
	{
		if (flipping)
		{
			if (up)
			{
				gameObject->rotation.y += elapsedTime * (speed * 2);
			}
			else
			{
				gameObject->rotation.y -= elapsedTime * speed;
			}

			if (gameObject->rotation.y >= 315)
			{
				up = false;
			}
			else if (gameObject->rotation.y < 270)
			{
				up = true;
				flipping = false;
				gameObject->rotation.y = 270;
			}
		}
	}
	else
	{
		if (flipping)
		{
			if (up)
			{
				gameObject->rotation.y -= elapsedTime * (speed * 2);
			}
			else
			{
				gameObject->rotation.y += elapsedTime * speed;
			}

			if (gameObject->rotation.y <= 45)
			{
				up = false;
			}
			else if (gameObject->rotation.y > 90)
			{
				up = true;
				flipping = false;
				gameObject->rotation.y = 90;
			}
		}
	}
}

void FlipComponent::setHandle(bool handle)
{
	this->flipping = handle;
}
