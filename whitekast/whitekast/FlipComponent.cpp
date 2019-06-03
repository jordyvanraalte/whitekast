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

			if (gameObject->rotation.y >= 405)
			{
				up = false;
			}
			else if (gameObject->rotation.y < 360)
			{
				up = true;
				flipping = false;
				gameObject->rotation.y = 360;
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

			if (gameObject->rotation.y <= 135)
			{
				up = false;
			}
			else if (gameObject->rotation.y > 180)
			{
				up = true;
				flipping = false;
				gameObject->rotation.y = 180;
			}
		}
	}
}

void FlipComponent::setHandle(bool handle)
{
	this->flipping = handle;
}
