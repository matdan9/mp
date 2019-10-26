#pragma once

#include "../core/Core.h"
#include "../core/Core.h"
#include "../core/GameObject.h"
#include <stdio.h>

#define startZise 10

class DArray {

private:
	int currentLength;
	GameObject *gameObjects;
	int nextSlot;

public:
	DArray();

	DArray(GameObject gos[], int length);

	void add(GameObject go);

	void extendArray();

	void printContent();

	GameObject get(int index);

	int fullSize();

	int size();

private:
	void transfer(GameObject *OB, int length);

	void addGameObject(GameObject go);

};
