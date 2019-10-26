#pragma once
#include "Core.h"
#include <stdio.h>
#include "../components/Time.h"
#include "Renderer.h"
#include "../components/Component.h"
#include <thread>
#include "../components/InputListenner.h"

#define gameUpdate 1/60

class App{
private:
	Renderer renderer = Renderer();
	char running;
	void startGl();
	void runCoreLoop();
	void updateGame();


public:
	App();
	~App();

	void changeInputListenner(InputListenner *);
	void start();
};