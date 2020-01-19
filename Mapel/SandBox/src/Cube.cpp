#include "Cube.h"

Cube::Cube() {
	speed = 0;
	position = MVector(0, 0);
	dimention = MVector(0, 0);
}

Cube::~Cube() {}

Cube::Cube(MVector positions, MVector dimentions, float speed) {
	position = positions;
	dimention = dimentions;
	this->speed = speed;
}

void Cube::moveLeft() {
	position.increaseVec(speed * -1, 0);
}

void Cube::moveRight() {
	position.increaseVec(speed, 0);
}

void Cube::moveDown() {
	position.increaseVec(0, speed * -1);
}

void Cube::moveUp() {
	position.increaseVec(0, speed);
}

void Cube::test() {
	printf("le cube\n");
}