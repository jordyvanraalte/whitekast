// whitekast.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Game.h"
#include <GL/freeglut.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "WhitekastObject.h"
#include "WhitekastVision.h"
#include <vector>


Game *game = nullptr;

int main(int argc, char *argv[]) 
{	
	game = new Game("Whitekast!", argc, argv);
	game->startGame();
	
	return 0;
}
