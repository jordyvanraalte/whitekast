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
	float radius = 0.5f;
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

			for (Component* c : gameObject->getComponents())
			{
				if (LineCollideComponent* l = dynamic_cast<LineCollideComponent*>(c))
				{
					l->flipHitbox((cos(gameObject->rotation.y) * radius) * 100, (sin(gameObject->rotation.y) * radius) * 100);
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
				for (Component* c : gameObject->getComponents())
				{
					if (LineCollideComponent* l = dynamic_cast<LineCollideComponent*>(c))
					{
						l->flipHitbox((cos(gameObject->rotation.y) * radius) * 100, (sin(gameObject->rotation.y) * radius) * 100);
					}
				}
			}
			else
			{
				gameObject->rotation.y += elapsedTime * speed;
				for (Component* c : gameObject->getComponents())
				{
					if (LineCollideComponent* l = dynamic_cast<LineCollideComponent*>(c))
					{
						l->flipHitbox((cos(gameObject->rotation.y) * radius) * 100, (sin(gameObject->rotation.y) * radius) * 100);
					}
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
