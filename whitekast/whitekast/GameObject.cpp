#include "GameObject.h"
#include "DrawComponent.h"
#include "CollideComponent.h"
#include <GL/freeglut.h>

GameObject::GameObject()
{
	position = Vec3f(0, 0, 0);
	rotation = Vec3f(0, 0, 0);
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
	if (!drawComponent)
		return;

	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glRotatef(rotation.x, 1, 0, 0);
	glRotatef(rotation.y, 0, 1, 0);
	glRotatef(rotation.z, 0, 0, 1);
	glScalef(scale.x, scale.y, scale.z);
	drawComponent->draw();
	glPopMatrix();
}

Hitbox* GameObject::getHitbox() const
{
	if (!collideComponent)
		return nullptr;

	return collideComponent->getHitbox();
}

void GameObject::update(float elapsedTime)
{
	vectemp = velocity;
	vectemp.applyTime(elapsedTime);

	for (auto c : components)
		c->update(elapsedTime);

	position = position + vectemp;
}
