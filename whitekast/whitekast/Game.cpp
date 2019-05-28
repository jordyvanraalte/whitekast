#include "wtypes.h"
#include "Game.h"
#include <math.h>
#include "GameObject.h"
#include "WhitekastObject.h"
#include "WhitekastVision.h"
#include "CubeComponent.h"
#include "WorldComponent.h"
#include "Vec.h"
#include "FlipComponent.h"
#include <vector>
#include <iostream>
#include "World.h"
#include <GL/freeglut.h>
#include "AudioManager.h"

std::list<GameObject*> objects;
static World* world;

int horizontal = 0;
int vertical = 0;

Game::Game(const char * title, int argc, char * argv[])
{
	initGlut(title, argc, argv);
	world = new World(horizontal, vertical, objects);
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

	initFlippers();

	std::vector<WhitekastObject*> whitekastObjects = initVision();
	for (auto wkObject : whitekastObjects) {
		GameObject* gameObject = new GameObject();
		gameObject->addComponent(wkObject);
		objects.push_back(gameObject);
	}

	initObjects();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(horizontal, vertical);
	glutCreateWindow(title);

	glEnable(GL_DEPTH_TEST);

	glutIdleFunc([]() { World::getWorld()->idle();  });
	glutDisplayFunc([]() { World::getWorld()->display(); });
	glutReshapeFunc([](int horizontal, int vertical) { World::getWorld()->reshape(horizontal, vertical); });
	glutKeyboardFunc([](unsigned char key, int mouseX, int mouseY) { World::getWorld()->keyboard(key, mouseX, mouseY); });
	glutKeyboardUpFunc([](unsigned char key, int mouseX, int mouseY) { World::getWorld()->keyboardUp(key, mouseX, mouseY); });
	glutPassiveMotionFunc([](int mouseX, int mouseY) {World::getWorld()->mousePassiveMotion(mouseX, mouseY); });
	glutMouseFunc([](int button, int state, int mouseX, int mouseY) {World::getWorld()->mouseClick(button, state, mouseX, mouseY); });
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


void Game::initObjects()
{
	GameObject* testCube = new GameObject();
	testCube->addComponent(new CubeComponent(1));
	testCube->addComponent(new FlipComponent());
	testCube->position = ::Vec3f(0, 0, -3);
	testCube->rotationPoint = ::Vec3f(testCube->position.x + 1, testCube->position.y, testCube->position.z + 1);
	objects.push_back(testCube);

	//GameObject* roomCube = new GameObject();	//roomCube->addComponent(new WorldComponent(10));
	//roomCube->position = ::Vec3f(0, 0, 0);
	//objects.push_back(roomCube);
}

void Game::clean() 
{

}

void Game::initFlippers()
{
	::Vec3f scale = ::Vec3f(0.1, 0.1, 0.1);
	GameObject* flipperLeft = new GameObject("Models/Flippers/flipperblend.obj");
	flipperLeft->position = ::Vec3f(0, 0, 0);
	flipperLeft->scale = scale;
	flipperLeft->addComponent(new FlipComponent());
	objects.push_back(flipperLeft);
	GameObject* flipperRight = new GameObject("Models/Flippers/flipperblend.obj");
	flipperRight->position = ::Vec3f(0, 0, 5);
	flipperRight->scale = scale;
	flipperRight->addComponent(new FlipComponent());
	objects.push_back(flipperRight);
}
