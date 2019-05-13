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

Game::Game(const char* title, int argc, char* argv[]) {
	int horizontal = 0;
	int vertical = 0;
	getDesktopResolution(horizontal, vertical);

	objects.push_back(GameObject());


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(horizontal, vertical);
	glutCreateWindow(title);
	
	glutIdleFunc([]() { World::getWorld()->idle();  });
	glutDisplayFunc([]() { World::getWorld()->display(objects); });

	glutMainLoop();

}

Game::~Game() {
}

void Game::handleEvents() {

}

void Game::update()	{

}

void Game::getDesktopResolution(int& horizontal, int& vertical) {
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	horizontal = desktop.right;
	vertical = desktop.bottom;
}

void Game::clean() {

}

