// whitekast.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include "pch.h"
#include "Game.h"
#include <GL/freeglut.h>
#include <opencv2/opencv.hpp>
#include <iostream>

Game *game = nullptr;

int main(int argc, char *argv[]) {

	game = new Game("WhiteKast!", argc, argv);
	return 0;
}
