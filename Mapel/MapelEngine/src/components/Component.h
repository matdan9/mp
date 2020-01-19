#pragma once
#include "../core/GameObject.h"

class Component
{
public:
	Component();
	~Component();

	void functionTest();
	virtual void runFunction();
};

