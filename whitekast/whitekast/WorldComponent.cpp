#include "WorldComponent.h"
#include <GL/freeglut.h>

WorldComponent::WorldComponent(float size, Texture texture1, Texture texture2, Texture texture3, Texture texture4) : texture1(0), texture2(0), texture3(0), texture4(0)
{
	this->size = size;
	this->texture1 = texture1;
	this->texture2 = texture2;
	this->texture3 = texture3;
	this->texture4 = texture4;
}


WorldComponent::~WorldComponent()
{
}

void WorldComponent::draw() 
{
	glBegin(GL_QUADS);
	glColor3f(0, 0, 1);
	glVertex3f(-size, -size, -size);
	glVertex3f(-size, -size, size);
	glVertex3f(-size, size, size);
	glVertex3f(-size, size, -size);

	glColor3f(0, 1, 0);
	glVertex3f(size, -size, -size);
	glVertex3f(size, -size, size);
	glVertex3f(size, size, size);
	glVertex3f(size, size, -size);

	glColor3f(0, 1, 1);
	glVertex3f(-size, -size, -size);
	glVertex3f(-size, -size, size);
	glVertex3f(size, -size, size);
	glVertex3f(size, -size, -size);

	glColor3f(1, 0, 0);
	glVertex3f(-size, size, -size);
	glVertex3f(-size, size, size);
	glVertex3f(size, size, size);
	glVertex3f(size, size, -size);

	glColor3f(1, 0, 1);
	glVertex3f(-size, -size, -size);
	glVertex3f(-size, size, -size);
	glVertex3f(size, size, -size);
	glVertex3f(size, -size, -size);

	glColor3f(1, 1, 1);
	glVertex3f(-size, -size, size);
	glVertex3f(-size, size, size);
	glVertex3f(size, size, size);
	glVertex3f(size, -size, size);

	glEnd();

}

void WorldComponent::drawWithTextures()
{
	glEnable(GL_TEXTURE_2D);
	texture1.bind();

	glBegin(GL_QUADS);
	glVertex3f(-size, -size, -size);
	glVertex3f(-size, -size, size);
	glVertex3f(-size, size, size);
	glVertex3f(-size, size, -size);

	texture2.bind();
	glVertex3f(size, -size, -size);
	glVertex3f(size, -size, size);
	glVertex3f(size, size, size);
	glVertex3f(size, size, -size);

	texture3.bind();
	glVertex3f(-size, -size, -size);
	glVertex3f(-size, -size, size);
	glVertex3f(size, -size, size);
	glVertex3f(size, -size, -size);

	texture4.bind();
	glVertex3f(-size, size, -size);
	glVertex3f(-size, size, size);
	glVertex3f(size, size, size);
	glVertex3f(size, size, -size);


	glColor3f(0, 0, 1);
	glVertex3f(-size, -size, -size);
	glVertex3f(-size, size, -size);
	glVertex3f(size, size, -size);
	glVertex3f(size, -size, -size);

	glVertex3f(-size, -size, size);
	glVertex3f(-size, size, size);
	glVertex3f(size, size, size);
	glVertex3f(size, -size, size);

	glEnd();
}

