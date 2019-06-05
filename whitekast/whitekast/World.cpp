#include "World.h"
#include "GameObject.h"
#include "WhitekastObject.h"
#include "CubeComponent.h"
#include <GL/freeglut.h>
#include <iostream>

struct Camera
{
	float posX = 0;
	float posY = 0;
	float rotX = 40;
	float rotY = 0;
	float posZ = -4;
} camera;

static World* world;
World::World(int horizontal, int vertical, std::list<GameObject*>& objectlist, GameObject* ball)
{
	world = this;
	width = horizontal;
	height = vertical;
	lastFrameTime = 0;
	
	gameObjects = objectlist;
	this->ball = ball;

	collisionManager = new CollisionManager();

	glEnable(GL_DEPTH_TEST);
	ZeroMemory(keys, sizeof(keys));
}

World::~World() 
{
	delete world;
}

World* World::getWorld()
{
	//if (world != NULL) {
		//world = new World(1920, 1080);
	//}
	return world;
}

void World::makePlatform()
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

void World::display()
{
	glClearColor(0.6f, 0.6f, 1, 1 );
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, width / (float)height, 0.1f, 500.0f);
	
	glRotatef(camera.rotX, 1, 0, 0);
	glRotatef(camera.rotY, 0, 1, 0);
	glTranslatef(camera.posX, camera.posZ, camera.posY);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3f(0, 0, 1);
	ball->draw();

	glColor3f(0, 0, 0);
	for (auto object : gameObjects) 
	{
		glPushMatrix();
		
		if (object->isVisionObject == false)
			glRotatef(-10, 1, 0, 0);

		object->draw();
		glPopMatrix();
	}

	glutSwapBuffers();
}

void World::reshape(int horizontal, int vertical)
{
	width = horizontal;
	height = vertical;
}

void World::move(const float angle, const float fac)
{
	camera.posX += cosf((camera.rotY + angle) / 180 * M_PI) * fac;
	camera.posY += sinf((camera.rotY + angle) / 180 * M_PI) * fac;
}

void World::idle(void)
{
	float frameTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	deltaTime = frameTime - lastFrameTime;
	lastFrameTime = frameTime;

	const float speed = 3;
	if (keys['A']) move(0, deltaTime*speed);
	if (keys['D']) move(180, deltaTime*speed);
	if (keys['W']) move(90, deltaTime*speed);
	if (keys['S']) move(270, deltaTime*speed);
	if (keys['Q']) camera.posZ += deltaTime * speed;
	if (keys['E']) camera.posZ -= deltaTime * speed;
	
	ball->update(deltaTime);
	for (auto o : gameObjects)
	{
		collisionManager->isColliding(ball, o);
		o->update(deltaTime);
		o->handleEvent(deltaTime);
	}
	
		
	glutPostRedisplay();
}

void World::keyboard(unsigned char key, int mouseX, int mouseY)
{
	switch (key)
	{
		case 27:
			exit(0);
			break;
		default:
			break;
	}
	keys[key] = true;
}

void World::keyboardUp(unsigned char key, int mouseX, int mouseY)
{
	keys[key] = false;
}

bool justMovedMouse = false;
void World::mousePassiveMotion(int x, int y)
{
	int dx = x - width / 2;
	int dy = y - height / 2;
	if ((dx != 0 || dy != 0) && abs(dx) < 400 && abs(dy) < 400 && !justMovedMouse)
	{
		camera.rotY += dx / 10.0f;
		camera.rotX += dy / 10.0f;
	}
	if (!justMovedMouse)
	{
		glutWarpPointer(width / 2, height / 2);
		justMovedMouse = true;
	}
	else
		justMovedMouse = false;
}

void World::mouseClick(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		for (auto o : gameObjects)
		{
			for (auto c : o->getComponents())
			{
				c->setHandle(true);
			}
		}
	}
}

