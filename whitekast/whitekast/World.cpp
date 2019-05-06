#include "pch.h"
#include "World.h"
#include <GL/freeglut.h>



static World* world;

World::World(const char* titel, int argc, char *argv[], int width, int height) {

	//window inits
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(width, height);
	glutCreateWindow(titel);
	world = this;

	//functions inits
	glutIdleFunc([]() {world->idle(); });
	glutDisplayFunc([]() {world->display(); });
	glutMainLoop();
}


World::~World() {
	delete world;
}

World* World::getWorld(const char* titel, int argc, char* argv[], int width, int height)
{
	if (world != NULL) {
		world = new World(titel, argc, argv, width, height);
	}
	return world;
}

void World::idle(void){
}

void World::display(void){
}

void World::reshape(int width, int height){
}

