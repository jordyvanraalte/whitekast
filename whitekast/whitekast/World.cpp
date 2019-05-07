#include "pch.h"
#include "World.h"
#include <GL/freeglut.h>
#include <iostream>



static World* world;

World::World() {

	
}


World::~World() {
	delete world;
}

World* World::getWorld()
{
	if (world != NULL) {
		world = new World();
	}
	return world;
}

void World::idle(void){
}

void World::display(void){
}

void World::reshape(int width, int height){
}

