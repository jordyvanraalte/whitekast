#include "WorldComponent.h"
#include <GL/freeglut.h>

WorldComponent::WorldComponent(float size, Texture texture1, Texture texture2, Texture texture3, Texture texture4, Texture texture5)
{
	this->size = size;
	this->texture1 = texture1;
	this->texture2 = texture2;
	this->texture3 = texture3;
	this->texture4 = texture4;
	this->texture5 = texture5;
}


WorldComponent::~WorldComponent()
{

}

void WorldComponent::draw() 
{
	glEnable(GL_TEXTURE_2D);
	glColor3f(1, 1, 1);

	texture1.bind();
	glBegin(GL_QUADS);
	glTexCoord2f(1, 0);	glVertex3f(-size, -size, -size);
	glTexCoord2f(0, 0); glVertex3f(-size, -size, size);
	glTexCoord2f(0, 1); glVertex3f(-size, size, size);
	glTexCoord2f(1, 1); glVertex3f(-size, size, -size);
	glEnd();

	texture2.bind();
	glBegin(GL_QUADS);
	glTexCoord2f(1, 0); glVertex3f(size, -size, -size);
	glTexCoord2f(0, 0); glVertex3f(size, -size, size);
	glTexCoord2f(0, 1); glVertex3f(size, size, size);
	glTexCoord2f(1, 1); glVertex3f(size, size, -size);
	glEnd();


	texture3.bind();
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-size, -size, -size);
	glTexCoord2f(0, 1); glVertex3f(-size, -size, size);
	glTexCoord2f(1, 1); glVertex3f(size, -size, size);
	glTexCoord2f(1, 0); glVertex3f(size, -size, -size);
	glEnd();

	texture4.bind();
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-size, size, -size);
	glTexCoord2f(0, 1); glVertex3f(-size, size, size);
	glTexCoord2f(1, 1); glVertex3f(size, size, size);
	glTexCoord2f(1, 0); glVertex3f(size, size, -size);
	glEnd();


	texture5.bind();
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-size, -size, -size);
	glTexCoord2f(0, 1); glVertex3f(-size, size, -size);
	glTexCoord2f(1, 1); glVertex3f(size, size, -size);
	glTexCoord2f(1, 0); glVertex3f(size, -size, -size);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(-size, -size, size);	//Behind
	glVertex3f(-size, size, size);
	glVertex3f(size, size, size);
	glVertex3f(size, -size, size);
	glBindTexture(GL_TEXTURE_2D, 0);
	glEnd();
	glColor3f(1, 1, 1);
}
