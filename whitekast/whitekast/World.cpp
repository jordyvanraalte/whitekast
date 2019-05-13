#include "World.h"
#include "GameObject.h"
#include <GL/freeglut.h>
#include <iostream>


static World* world;
int width, height;
float lastFrameTime;

float lookAtX;
float lookAtY;
bool keys[255];
const float M_PI = 3.14159265358979323846;

struct Camera
{
	float posX = 0;
	float posY = -4;
	float rotX = 0;
	float rotY = 0;
	float posZ = 0;
} camera;

World::World(int horizontal, int vertical)
{
	width = horizontal;
	height = vertical;
	lastFrameTime = 0;
}

World::~World() 
{
	delete world;
}

World* World::getWorld()
{
	if (world != NULL) {
		world = new World(1920, 1080);
	}
	return world;
}

World* World::createWorld(int horizontal, int vertical)
{
	width = horizontal;
	height = horizontal;
	world = new World(width, height);

	return world;
}

void makePlatform()
{
	glMatrixMode(GL_MODELVIEW);
	glBegin(GL_QUADS);
	glColor4f(1, 0, 1, 1);
	glVertex3f(-10, 0, -10);
	glVertex3f(-10, 0,  10);
	glVertex3f( 10, 0,  10);
	glVertex3f( 10, 0, -10);

	glEnd();
}

void World::display(std::vector<GameObject> objects)
{
	glClearColor(0.6f, 0.6f, 1, 1);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, width / (float)height, 0.1f, 50.0f);
	
	makePlatform();

	for (GameObject &object : objects) 
	{
		object.draw();
	}

	glutSwapBuffers();
}

void World::reshape(int horizontal, int vertical)
{
	width = horizontal;
	height = vertical;
}

void move(float angle, float fac)
{
	camera.posX += (float)cos((camera.rotY + angle) / 180 * M_PI) * fac;
	camera.posY += (float)sin((camera.rotY + angle) / 180 * M_PI) * fac;
}

void World::idle(void)
{
	float frameTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	float deltaTime = frameTime - lastFrameTime;
	lastFrameTime = frameTime;

	const float speed = 3;
	if (keys['a']) move(0, deltaTime*speed);
	if (keys['d']) move(180, deltaTime*speed);
	if (keys['w']) move(90, deltaTime*speed);
	if (keys['s']) move(270, deltaTime*speed);

	glutPostRedisplay();
}

void World::keyboard(unsigned char key, int mouseX, int mouseY)
{
	switch (key)
	{
		default:

		break;
	}
}

void World::keyboardUp(unsigned char key, int mouseX, int mouseY)
{
	keys[key] = false;
}
