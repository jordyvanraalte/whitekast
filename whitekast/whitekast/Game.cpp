#include "pch.h"
#include "wtypes.h"
#include "Game.h"
#include "Player.h"
#include <iostream>
#include "World.h"
#include <GL/freeglut.h>

using namespace std;

Player player;

Game::Game(const char* title, int argc, char* argv[]) {
	int horizontal = 0;
	int vertical = 0;
	getDesktopResolution(horizontal, vertical);


	World* world = World::getWorld();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(horizontal, vertical);
	glutCreateWindow(title);
	glutDisplayFunc([]() {});
	
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

