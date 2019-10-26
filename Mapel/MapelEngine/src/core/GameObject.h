#pragma once
#include "Core.h"
#include <string.h>
#include "../components/MVector.h"

class GameObject {
public:
	char name[20 + 1] = "allo";
	MVector* position;
	MVector* dimention;

	GameObject();
	GameObject(const char *name);
	~GameObject();
};