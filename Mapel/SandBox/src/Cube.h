#pragma once
#include "../../MapelEngine/src/Mapel.h"
#include "../../MapelEngine/src/components/Component.h"
#include <stdio.h>
#include "../../MapelEngine/src/components/InputListenner.h"

class Cube: public GameObject {
private:
	float speed;
public:
	Cube();
	~Cube();
	Cube(MVector, MVector, float);
	void moveLeft();
	void moveRight();
	void moveDown();
	void moveUp();
	void test();
};

