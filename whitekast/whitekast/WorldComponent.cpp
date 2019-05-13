#include "WorldComponent.h"
#include <GL/freeglut.h>

WorldComponent::WorldComponent()
{
}


WorldComponent::~WorldComponent()
{
}

void WorldComponent::draw() 
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glBegin(GL_QUADS);
	glColor4f(1, 0, 1, 1);
	glVertex3f(-10, 0, -10);
	glVertex3f(-10, 0, 10);
	glVertex3f(10, 0, 10);
	glVertex3f(10, 0, -10);

	glEnd();
}
