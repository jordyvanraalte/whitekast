#include "GameObject.h"
#include "FlipComponent.h"
#include "DrawComponent.h"
#include "CollideComponent.h"
#include <GL/freeglut.h>
#include <iostream>

GameObject::GameObject(bool isVisionObject)
{
	position = Vec3f(0, 0, 0);
	rotation = Vec3f(0, 0, 0);
	scale = Vec3f(1, 1, 1);
	bounceFactor = 1.0f;
	this->isVisionObject = isVisionObject;
	rotationPoint = position;
	isCollider = false;
	isColliding = false;
}

GameObject::~GameObject()
{

}

void GameObject::addComponent(Component* component)
{
	component->setGameObject(this);
	components.push_back(component);

	if (!drawComponent)
		drawComponent = dynamic_cast<DrawComponent*>(component);

	if (!flipComponent)
		flipComponent = dynamic_cast<FlipComponent*>(component);

	if (!collideComponent)
		collideComponent = dynamic_cast<CollideComponent*>(component);
	
}

void GameObject::loadModel(const std::string& fileName)
{
}

std::list<Component*> GameObject::getComponents()
{
	return components;
}

void GameObject::draw()
{
	if (!model) {
		if (!drawComponent)
			return;

		glPushMatrix();
		glTranslatef(rotationPoint.x, rotationPoint.y, rotationPoint.z);
		glRotatef(rotation.x, 1, 0, 0);
		glRotatef(rotation.y, 0, 1, 0);
		glRotatef(rotation.z, 0, 0, 1);
		glTranslatef(position.x - rotationPoint.x, position.y - rotationPoint.y, position.z - rotationPoint.z);
		glScalef(scale.x, scale.y, scale.z);
		glColor3f(color.x, color.y, color.z);
		drawComponent->draw();
		glPopMatrix();
	}
	else {
		glPushMatrix();
		glTranslatef(rotationPoint.x, rotationPoint.y, rotationPoint.z);
		glRotatef(rotation.x, 1, 0, 0);
		glRotatef(rotation.y, 0, 1, 0);
		glRotatef(rotation.z, 0, 0, 1);
		glTranslatef(position.x - rotationPoint.x, position.y - rotationPoint.y, position.z - rotationPoint.z);
		glScalef(scale.x, scale.y, scale.z);
		model->draw();
		glPopMatrix();
	}
}

void GameObject::setCoordinates(std::vector<cv::Point> coordinates)
{
	this->coordinates = coordinates;
}

double GameObject::getRadius()
{
	bool first = true;
	cv::Point highest1, highest2;

	for (const cv::Point point1 : this->coordinates)
	{
		for (const cv::Point point2 : this ->coordinates)
		{
			double length = sqrt((point2.x - point1.x) ^ 2 + (point2.y - point1.y));
			if (!first)
			{
				double lengthHighest = sqrt((highest2.x - highest1.x) ^ 2 + (highest2.y - highest1.y));
				if(length > lengthHighest)
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

	return 2;

}

Hitbox* GameObject::getHitbox() const
{
	if (!collideComponent)
		return nullptr;

	return collideComponent->getHitbox();
}

Hitbox* GameObject::getCircleBox() const
{
	if (!collideComponent)
		return nullptr;

	return collideComponent->getCirclebox();
}

void GameObject::update(float elapsedTime)
{
	for (auto c : components)
		c->update(elapsedTime);

	vectemp = velocity;
	vectemp.applyTime(elapsedTime);

	position = position + vectemp;
}

void GameObject::handleEvent(float elapsedTime)
{
	if (!flipComponent)
		return;

	flipComponent->handleEvent(elapsedTime);
}
