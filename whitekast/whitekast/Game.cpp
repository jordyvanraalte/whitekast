#include "wtypes.h"
#include "Game.h"
#include <math.h>
#include "GameObject.h"
#include "CubeComponent.h"
#include "WorldComponent.h"
#include <vector>
#include <iostream>
#include "World.h"
#include <GL/freeglut.h>

std::list<GameObject*> objects;
static World* world;

Game::Game(const char* title, int argc, char* argv[]) 
{
	int horizontal = 0;
	int vertical = 0;
	getDesktopResolution(horizontal, vertical);

	makeObjects();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(horizontal, vertical);
	glutCreateWindow(title);
	
	glEnable(GL_DEPTH_TEST);
	world = new World(horizontal, vertical, objects);

	glutIdleFunc([]() { World::getWorld()->idle();  });
	glutDisplayFunc([]() { World::getWorld()->display(); });
	glutReshapeFunc([](int horizontal, int vertical) { World::getWorld()->reshape(horizontal, vertical); });
	glutKeyboardFunc([](unsigned char key, int mouseX, int mouseY) { World::getWorld()->keyboard(key, mouseX, mouseY); });
	glutKeyboardUpFunc([](unsigned char key, int mouseX, int mouseY) { World::getWorld()->keyboardUp(key, mouseX, mouseY); });
	glutPassiveMotionFunc([](int mouseX, int mouseY) {World::getWorld()->mousePassiveMotion(mouseX, mouseY); });
	
	glutMainLoop();
}

Game::~Game() 
{

}

void Game::makeObjects()
{
	GameObject* testCube = new GameObject();
	testCube->addComponent(new CubeComponent(1));
	testCube->position = Vec3f(0, 0, -3);
	objects.push_back(testCube);

	GameObject* roomCube = new GameObject();
	roomCube->addComponent(new CubeComponent(10));
	roomCube->position = Vec3f(0, 0, 0);
	objects.push_back(roomCube);
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

