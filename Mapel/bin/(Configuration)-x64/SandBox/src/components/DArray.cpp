#include "DArray.h"

#define startZise 10

DArray::DArray() {
	currentLength = startZise;
	gameObjects = new GameObject[currentLength];
	nextSlot = 0;
}

DArray::DArray(GameObject gos[], int length) {
	currentLength = length;
	nextSlot = length;
	delete[] gameObjects;
	gameObjects = gos;
	extendArray();
}

void DArray::add(GameObject go) {
	if (nextSlot < currentLength - 1) {
		addGameObject(go);
		return;
	}
	extendArray();
	addGameObject(go);
}

void DArray::extendArray() {
	currentLength *= 2;
	GameObject *newGOs = new GameObject[currentLength];
	GameObject *toDelete = gameObjects;
	transfer(newGOs, currentLength / 2);
	gameObjects = newGOs;
	delete[] toDelete;
}

void DArray::printContent() {
	for (int i = 0; i < currentLength; ++i) {
		printf("%s\n", gameObjects[i].name);
	}
}

GameObject DArray::get(int index) {
	if (index < currentLength && index > -1) {
		return gameObjects[index];
	}
	return GameObject();
}

int DArray::fullSize() {
	return currentLength;
}

int DArray::size() {
	return nextSlot;
}

void DArray::transfer(GameObject *OB, int length) {
	for (int i = 0; i < length; ++i) {
		OB[i] = gameObjects[i];
	}
}

void DArray::addGameObject(GameObject go) {
	gameObjects[nextSlot++] = go;
}