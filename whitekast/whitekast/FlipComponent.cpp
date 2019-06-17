#include "FlipComponent.h"
#include "LineColliderComponent.h"
#include "GameObject.h"
#include <GL/freeglut.h>
#include <math.h>  

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
	float radius = 0.43f;
	if (left)
	{
		if (flipping)
		{
			if (up)
			{
				gameObject->rotation.y += elapsedTime * (speed * 2);
				gameObject->bounceFactor = 2.5f;
			}
			else
			{
				gameObject->rotation.y -= elapsedTime * speed;
				gameObject->bounceFactor = 0.5f;
			}

			for (Component* c : gameObject->getComponents())
			{
				if (LineCollideComponent* l = dynamic_cast<LineCollideComponent*>(c))
				{
					float newX = -(sin((gameObject->rotation.y - 90) * DEG_TO_RAD) * radius);
					float newZ = -(cos((gameObject->rotation.y - 90) * DEG_TO_RAD) * radius);
					l->flipHitbox(newX, newZ);
				}
			}

			if (gameObject->rotation.y >= 300)
			{
				up = false;
			}
			else if (gameObject->rotation.y < 255)
			{
				up = true;
				flipping = false;
				gameObject->rotation.y = 255;
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
				gameObject->bounceFactor = 2.5f;
			}
			else
			{
				gameObject->rotation.y += elapsedTime * speed;
				gameObject->bounceFactor = 0.5f;
			}

			for (Component* c : gameObject->getComponents())
			{
				if (LineCollideComponent* l = dynamic_cast<LineCollideComponent*>(c))
				{
					float newX = -(sin((gameObject->rotation.y - 90) * DEG_TO_RAD) * radius);
					float newZ = -(cos((gameObject->rotation.y - 90) * DEG_TO_RAD) * radius);
					l->flipHitbox(newX, newZ);
				}
			}

			if (gameObject->rotation.y <= 50)
			{
				up = false;
			}
			else if (gameObject->rotation.y > 105)
			{
				up = true;
				flipping = false;
				gameObject->rotation.y = 105;
			}
			
		}
	}
}

void FlipComponent::setHandle(bool handle)
{
	this->flipping = handle;
}
