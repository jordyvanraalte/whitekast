#include "WhitekastObject.h"

std::vector<Point> coordinates;
ObjectColor objectColor;

WhitekastObject::WhitekastObject(ObjectColor color){
	objectColor = color;
}

WhitekastObject::~WhitekastObject(){
	delete(this);
}

std::vector<Point> getCoordinates() {
	return coordinates;
}

//void setCoordinates(std::vector<Point> newCoordinates) {
//	coordinates = newCoordinates;
//}

Scalar getObjectColor() {
	return objectColor;
}

void setObjectColor(ObjectColor color) {
	objectColor = color;
}