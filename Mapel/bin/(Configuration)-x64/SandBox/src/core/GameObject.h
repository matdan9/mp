#pragma once
#include "Core.h"
#include <string.h>
class GameObject {
public:
	char name[20 + 1] = "allo";

	GameObject();
	GameObject(const char *name);
};