#include "CubeComponent.h"
#include <GL/freeglut.h>

CubeComponent::CubeComponent(const float size)
{
	this->size = size;
}

CubeComponent::~CubeComponent()
{

}

void CubeComponent::draw()
{
	glBegin(GL_QUADS);
	glColor3f(0, 0, 1);					//links pacman
	glVertex3f(-size, -size, -size);
	glVertex3f(-size, -size, size);
	glVertex3f(-size, size, size);
	glVertex3f(-size, size, -size);

	glColor3f(0, 1, 0);					//rechts minecraft
	glVertex3f(size, -size, -size);
	glVertex3f(size, -size, size);
	glVertex3f(size, size, size);
	glVertex3f(size, size, -size);

	glColor3f(0, 1, 1);					//vloer
	glVertex3f(-size, -size, -size);
	glVertex3f(-size, -size, size);
	glVertex3f(size, -size, size);
	glVertex3f(size, -size, -size);

	glColor3f(1, 0, 0);					//roof
	glVertex3f(-size, size, -size);
	glVertex3f(-size, size, size);
	glVertex3f(size, size, size);
	glVertex3f(size, size, -size);

	glColor3f(1, 0, 1);					//voor shrek
	glVertex3f(-size, -size, -size);
	glVertex3f(-size, size, -size);
	glVertex3f(size, size, -size);
	glVertex3f(size, -size, -size);

	glColor3f(1, 1, 1);					//behind
	glVertex3f(-size, -size, size);
	glVertex3f(-size, size, size);
	glVertex3f(size, size, size);
	glVertex3f(size, -size, size);

	glBindTexture(GL_TEXTURE_2D, 0);
	glEnd();
	glColor3f(1, 1, 1);
}
