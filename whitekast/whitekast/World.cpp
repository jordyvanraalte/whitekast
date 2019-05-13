#include "World.h"
#include "GameObject.h"
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

void World::display(std::vector<GameObject> objects){
	glClearColor(0.6f, 0.6f, 1, 1);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	
	for (GameObject &object : objects) {
		object.draw();
	}

	glutSwapBuffers();
}

void World::reshape(int width, int height){
}

