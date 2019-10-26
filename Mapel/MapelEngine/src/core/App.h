#pragma once
#include "Core.h"
#include <stdio.h>
#include "../components/Time.h"
#include "Renderer.h"
#include "../components/Component.h"
#include <thread>
#include "../components/InputListenner.h"
#include "GameObject.h"
#include <vector>

#define gameUpdate 1/60

class App{
private:
	Renderer renderer = Renderer();
	char running;
	std::vector<GameObject*> objs;

	void startGl();
	void runCoreLoop();
	void updateGame();

public:
	App();
	~App();

	void changeInputListenner(InputListenner *);
	void addObj(GameObject*);
	void start();
};