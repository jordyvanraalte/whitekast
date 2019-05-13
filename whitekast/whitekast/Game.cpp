#include "pch.h"
#include "wtypes.h"
#include "Game.h"
#include "Player.h"
#include "GameObject.h"
#include <vector>
#include <iostream>
#include "World.h"
#include <GL/freeglut.h>


Player player;
std::vector<GameObject> objects;	

Game::Game(const char* title, int argc, char* argv[]) 
{
	int horizontal = 0;
	int vertical = 0;
	getDesktopResolution(horizontal, vertical);

	objects.push_back(GameObject());

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(horizontal, vertical);
	glutCreateWindow(title);
	
	glEnable(GL_DEPTH_TEST);

	glutIdleFunc([]() { World::getWorld()->idle();  });
	glutDisplayFunc([]() { World::getWorld()->display(objects); });
	glutReshapeFunc([](int horizontal, int vertical) { World::getWorld()->reshape(horizontal, vertical); });
	glutKeyboardFunc([](unsigned char key, int mouseX, int mouseY) { World::getWorld()->keyboard(key, mouseX, mouseY); });
	glutKeyboardUpFunc([](unsigned char key, int mouseX, int mouseY) { World::getWorld()->keyboardUp(key, mouseX, mouseY); });
	
	glutMainLoop();
}

Game::~Game() 
{

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

