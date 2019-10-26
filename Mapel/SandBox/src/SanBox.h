#pragma once
#include "../../MapelEngine/src/Mapel.h"
#include "../../MapelEngine/src/components/Component.h"
#include <stdio.h>
#include "../../MapelEngine/src/components/InputListenner.h"
#include "Cube.h"

class SandBox : public Component{
public:
	int bob = 0;
	SandBox();
	~SandBox();
	void printTest();
};