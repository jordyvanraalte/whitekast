#include "wtypes.h"
#include "Game.h"
#include <math.h>
#include "GameObject.h"
#include "WhitekastObject.h"
#include "WhitekastVision.h"
#include "CubeComponent.h"
#include "WorldComponent.h"
#include "GravityComponent.h"
#include "ModelComponent.h"
#include "CollideComponent.h"
#include "CircleCollideComponent.h"
#include "Vec.h"
#include <vector>
#include <iostream>
#include "World.h"
#include <GL/freeglut.h>
#include "AudioManager.h"
#include "StateManager.h"
#include "CollisionManager.h"

std::list<GameObject*> objects;
static World* world;

int horizontal = 0;
int vertical = 0;

Game::Game(const char * title, int argc, char * argv[])
{
	initGlut(title, argc, argv);
	makeObjects();
	initObjects();
	world = new World(horizontal, vertical, objects);

	audiomanager = AudioManager::getInstance();
	audiomanager->playSound("audio/test.mpeg");
	audiomanager->playSound("audio/bumper_hit.wav");

	StateManager::getInstance();

	CollisionManager* collision = new CollisionManager();
	

}

Game::~Game()
{
}

void Game::startGame()
{
	glutMainLoop();
}

void Game::initGlut(const char * title, int argc, char * argv[])
{
	getDesktopResolution(horizontal, vertical);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(horizontal, vertical);
	glutCreateWindow(title);

	glEnable(GL_DEPTH_TEST);

	glutIdleFunc([]() { World::getWorld()->idle();  });
	glutDisplayFunc([]() { World::getWorld()->display(); });
	//glutDisplayFunc([]() { World::getWorld()->displayVisionObjects(whitekastObjects); });
	glutReshapeFunc([](int horizontal, int vertical) { World::getWorld()->reshape(horizontal, vertical); });
	glutKeyboardFunc([](unsigned char key, int mouseX, int mouseY) { World::getWorld()->keyboard(key, mouseX, mouseY); });
	glutKeyboardUpFunc([](unsigned char key, int mouseX, int mouseY) { World::getWorld()->keyboardUp(key, mouseX, mouseY); });
	glutPassiveMotionFunc([](int mouseX, int mouseY) {World::getWorld()->mousePassiveMotion(mouseX, mouseY); });
}

void Game::makeObjects()
{
	/*GameObject* testCube = new GameObject();
	testCube->addComponent(new CubeComponent(1));
	testCube->position = ::Vec3f(0, 0, -3);
	objects.push_back(testCube);

	GameObject* roomCube = new GameObject();
	roomCube->addComponent(new CubeComponent(10));
	roomCube->position = ::Vec3f(0, 0, 0);
	objects.push_back(roomCube);*/

	GameObject* testball = new GameObject();
	testball->addComponent(new ModelComponent("Models/Pinballs/pinball_3.1.obj", testball));
	testball->addComponent(new GravityComponent(::Vec3f(0, 0, 0.981)));
	testball->position = ::Vec3f(0, 0, -3);
	testball->addComponent(new CircleCollideComponent(testball));
	objects.push_back(testball);
}

void Game::handleEvents() 
{

}

void Game::update()	
{

}

void Game::getDesktopResolution(int& horizontal, int& vertical) 
{
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	horizontal = desktop.right;
	vertical = desktop.bottom;
}

void Game::clean() 
{

}

void Game::initObjects()
{
	GameObject* testCube = new GameObject();
	testCube->addComponent(new CubeComponent(1));
	testCube->position = ::Vec3f(0, -2, 0);
	objects.push_back(testCube);

	Texture texture1 = Texture("Texture/LeftWall");
	Texture texture2 = Texture("Texture/RightWall");
	Texture texture3 = Texture("Texture/floor");
	Texture texture4 = Texture("Texture/Cealing");
	Texture texture5 = Texture("Texture/FrontWall");

}
