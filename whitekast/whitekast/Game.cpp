#include "pch.h"
#include "wtypes.h"
#include "Game.h"
#include "Player.h"
#include <iostream>
using namespace std;

Player player;

Game::Game(const char* title, int argc, char* argv[]) {
	int horizontal = 0;
	int vertical = 0;
	getDesktopResolution(horizontal, vertical);
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

