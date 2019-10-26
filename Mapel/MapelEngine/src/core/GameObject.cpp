#include "GameObject.h"

GameObject::GameObject() {
	strcmp(name, "Enter Name");
}

GameObject::GameObject(const char *name) {
	strcmp(name, name);
}

GameObject::~GameObject() {
	//delete position;
	//delete dimention;
}