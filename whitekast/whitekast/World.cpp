#include "World.h"
#include "GameObject.h"
#include "PointCounter.h"
#include "LivesCounter.h"
#include "HighScore.h"
#include "WhitekastObject.h"
#include "WhitekastVision.h"
#include "CubeComponent.h"
#include "FlipComponent.h"
#include <GL/freeglut.h>
#include <iostream>
#include <cstring>
#include "Game.h"
#include "HomeState.h"

std::list<GameObject*> gameObjects;
WhitekastVision vision;
float lastFrameTime;

float lookAtX;
float lookAtY;
bool keys[255];
static World* world;
int width, height;

struct Camera
{
	float posX = 1.5;
	float posY = -2;
	float posZ = -2;
	float rotX = -20;
	float rotY = 90;
} camera;

World::World(int horizontal, int vertical, std::list<GameObject*>& objectlist, WhitekastVision whitekastVision, GameObject* ball)
{
	world = this;
	width = horizontal;
	height = vertical;
	lastFrameTime = 0;
	
	gameObjects = objectlist;
	vision = whitekastVision;
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
		
		if (object->isVisionObject == false) {
			glRotatef(-90, 0, 1, 0);
			glRotatef(-10, 1, 0, 0);
			glTranslatef(2, 0, 0);
		}

		object->draw();
		glPopMatrix();
	}
	displayUI(PointCounter::getInstance()->getPoints(), LivesCounter::getInstance()->getLives(), HighScore::getInstance()->getHighScore());
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
	if (keys['R'])
	{
	
		ball->position = Vec3f(5.0f, -2, 1.5f);
		ball->velocity = Vec3f(0, 0, 0);
	}
	if(keys['B'])
	{
		StateManager::getInstance()->setState(new PlayState());
	}

	if(!dynamic_cast<HomeState*>(StateManager::getInstance()->getState()))
		ball->update(deltaTime);

	for (auto o : gameObjects)
	{
		collisionManager->isColliding(ball, o);
		o->update(deltaTime);
		o->handleEvent(deltaTime);
	}
	if (vision.getMotionLeft())
	{
		for (auto o : gameObjects)
		{
			for (Component* c : o->getComponents())
			{
				if (FlipComponent* f = dynamic_cast<FlipComponent*>(c))
				{
					if (f->isLeft())
					{
						c->setHandle(true);
					}					
				}
			}
		}
	}
	if (vision.getMotionRight())
	{
		for (auto o : gameObjects)
		{
			for (Component* c : o->getComponents())
			{
				if (FlipComponent* f = dynamic_cast<FlipComponent*>(c))
				{
					if (!f->isLeft())
					{
						c->setHandle(true);
					}
				}
			}
		}
	}

	if(ball->position.x < 0)
	{
		StateManager::getInstance()->setState(new DeathState());
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
		if (camera.rotY <= 20) {
			camera.rotY = 20;
		}
		else if (camera.rotY >= 160) {
			camera.rotY = 160;
		}
		camera.rotY += dx / 10.0f;

		if (camera.rotX <= -40) {
			camera.rotX = -40;
		}
		else if (camera.rotX >= 90) {
			camera.rotX = 90;
		}
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
	/*if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		for (auto o : gameObjects)
		{
			for (auto c : o->getComponents())
			{
				c->setHandle(true);
			}
		}
	}*/
}

void World::displayUI(int points, int lifepoints, int highScore)
{

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, width, height, 0.0, -1.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	//glPushMatrix();        ----Not sure if I need this
	glLoadIdentity();
	glDisable(GL_CULL_FACE);

	glClear(GL_DEPTH_BUFFER_BIT);
	glRotatef(180, 1, 0, 0);
	glTranslatef(0, -25, 0);
	glScalef(0.2, 0.2, 0.2);
	std::string tempString = "score: ";
	tempString = tempString + std::to_string(points);
	unsigned char score[256];
	std::copy(tempString.begin(), tempString.end(), score);

	score[tempString.length()] = 0;
	glutStrokeString(GLUT_STROKE_ROMAN, score);
	tempString = " lives: ";
	tempString = tempString + std::to_string(lifepoints);
	unsigned char lives[256];
	std::copy(tempString.begin(), tempString.end(), lives);
	lives[tempString.length()] = 0;
	glutStrokeString(GLUT_STROKE_ROMAN, lives);

	tempString = " Highscore: ";
	tempString = tempString + std::to_string(highScore);
	unsigned char high[256];
	std::copy(tempString.begin(), tempString.end(), high);
	high[tempString.length()] = 0;
	glutStrokeString(GLUT_STROKE_ROMAN, high);

	// Making sure we can render 3d again
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	//glPopMatrix();        ----and this?
}
