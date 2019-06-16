#include "LineColliderComponent.h"
#include "GameObject.h"

LineCollideComponent::LineCollideComponent(GameObject* gameobject, float wkscale)
{
	this->gameObject = gameobject;
	hitbox = new LinesHitbox(gameObject->coordinates, gameObject->scale, wkscale);

	bool first = true;
	cv::Point highest1, highest2;
	double lengthHighest = 0;

	for (const cv::Point point1 : gameobject->coordinates)
	{
		for (const cv::Point point2 : gameobject->coordinates)
		{
			double length = sqrt(pow(((point2.x*wkscale)*gameobject->scale.x) - ((point1.x*wkscale)*gameobject->scale.x), 2) + pow(((point2.y*wkscale)*gameobject->scale.y) - ((point1.y*wkscale)*gameobject->scale.y), 2));
			if (!first)
			{
				lengthHighest = sqrt(pow(((highest2.x*wkscale)*gameobject->scale.x) - ((highest1.x*wkscale)*gameobject->scale.x), 2) + pow(((highest2.y*wkscale)*gameobject->scale.y) - ((highest1.y*wkscale)*gameobject->scale.y), 2));
				if (length > lengthHighest)
				{
					highest1 = point1;
					highest2 = point2;
				}
			}
			else
			{
				highest1 = point1;
				highest2 = point2;
				first = false;
			}
		}
	}

	cv::Point position = cv::Point((((highest1.x + highest2.x) / 2)*wkscale)*gameObject->scale.x, (((highest1.y + highest2.y) / 2)*wkscale)*gameObject->scale.y);
	circle = new CircleHitbox(Vec3f(position.x, 0 , position.y), lengthHighest+4, Vec3f(1,1,1));
}

LineCollideComponent::~LineCollideComponent()
= default;

Hitbox* LineCollideComponent::getHitbox()
{
	return hitbox;
}

Hitbox* LineCollideComponent::getCirclebox()
{
	return circle;
}

void LineCollideComponent::update(float elapsedTime)
{
	hitbox->shiftColliders(gameObject->position);
}

void LineCollideComponent::flipHitbox(float x, float z)
{
	hitbox->flipColliders(::Vec3f(x, 0, z));
}
