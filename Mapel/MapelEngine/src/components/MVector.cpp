#include "MVector.h"

MVector::MVector() {}

MVector::~MVector() {}

MVector::MVector(float x, float y) {
	this->x = x;
	this->y = y;
}

float MVector::getX() {
	return x;
}
float MVector::getY() {
	return y;
}

void MVector::increaseVec(float x, float y) {
	this->x += x;
	this->y += y;
}

void MVector::increaseVec(MVector vec) {
	this->x += vec.x;
	this->y += vec.y;
}

float MVector::getLength() {
	return sqrt(pow(this->x, 2) + pow(this->y, 2));
}