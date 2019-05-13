// whitekast.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Game.h"
#include <GL/freeglut.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "WhitekastObject.h"
#include "WhitekastVision.h"

using namespace std;

Game *game = nullptr;
std::vector<WhitekastObject> whitekastObjects;

int main(int argc, char *argv[]) {
	whitekastObjects = initVision();

	game = new Game("WhiteKast!", argc, argv);

	return 0;
}
