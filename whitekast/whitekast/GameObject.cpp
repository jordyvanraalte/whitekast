#include "GameObject.h"
#include "FlipComponent.h"
#include "DrawComponent.h"
#include <GL/freeglut.h>

GameObject::GameObject(bool isVisionObject)
{
	position = Vec3f(0, 0, 0);
	rotation = Vec3f(0, 0, 0);
	this->isVisionObject = isVisionObject;
	rotationPoint = position;
}


GameObject::GameObject(std::string fileName)
{
	position = Vec3f(0, 0, 0);
	rotation = Vec3f(0, 0, 0);
	this->isVisionObject = false;
	rotationPoint = position;
	model = new ObjModel(fileName);
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

void GameObject::update(float elapsedTime)
{
	for (auto c : components)
		c->update(elapsedTime);
}

void GameObject::handleEvent(float elapsedTime)
{
	if (!flipComponent)
		return;

	flipComponent->handleEvent(elapsedTime);
}
