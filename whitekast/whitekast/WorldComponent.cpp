#include "WorldComponent.h"
#include <GL/freeglut.h>

WorldComponent::WorldComponent(float size, Texture texture1, Texture texture2, Texture texture3, Texture texture4, Texture texture5)
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
	glEnable(GL_TEXTURE_2D);
	texture1.bind();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);	glVertex3f(-size, -size, -size);
	glTexCoord2f(0, 1); glVertex3f(-size, -size, size);
	glTexCoord2f(1, 1); glVertex3f(-size, size, size);
	glTexCoord2f(1, 0); glVertex3f(-size, size, -size);

	texture2.bind();
	glTexCoord2f(0, 1); glVertex3f(size, -size, -size);
	glTexCoord2f(0, 1); glVertex3f(size, -size, size);
	glTexCoord2f(0, 1); glVertex3f(size, size, size);
	glTexCoord2f(0, 1); glVertex3f(size, size, -size);

	texture3.bind();
	glTexCoord2f(0, 1); glVertex3f(-size, -size, -size);
	glTexCoord2f(0, 1); glVertex3f(-size, -size, size);
	glTexCoord2f(0, 1); glVertex3f(size, -size, size);
	glTexCoord2f(0, 1); glVertex3f(size, -size, -size);

	texture4.bind();
	glTexCoord2f(0, 1); glVertex3f(-size, size, -size);
	glTexCoord2f(0, 1); glVertex3f(-size, size, size);
	glTexCoord2f(0, 1); glVertex3f(size, size, size);
	glTexCoord2f(0, 1); glVertex3f(size, size, -size);

	texture5.bind();
	glTexCoord2f(0, 1); glVertex3f(-size, -size, -size);
	glTexCoord2f(0, 1); glVertex3f(-size, size, -size);
	glTexCoord2f(0, 1); glVertex3f(size, size, -size);
	glTexCoord2f(0, 1); glVertex3f(size, -size, -size);

	glVertex3f(-size, -size, size);	//Behind
	glVertex3f(-size, size, size);
	glVertex3f(size, size, size);
	glVertex3f(size, -size, size);

	glEnd();
}
