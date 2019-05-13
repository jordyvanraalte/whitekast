#include <iostream>
#include "GameObject.h"

float posX = 0;
float posY = 0;
float posZ = 0;

GameObject::GameObject() {
}

GameObject::~GameObject() {

}



void GameObject::translate(float x, float y, float z) {
	posX = x;
	posY = y;
	posZ = z;
}

void GameObject::draw(void) {
	debug();
	glBegin(GL_QUADS);
	glEnd();
}

void GameObject::debug(void) {
	std::cout << typeid(this).name() << ": " << this << " Located: (" << posX << "," << posY << "," << posZ << ")" << "\n";
}
