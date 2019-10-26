#include "App.h"

App::App(){
	renderer = Renderer();
}

App::~App()
{
	running = 0;
}

void App::start() {
	//set up variables before start
	running = 1;
	std::thread glThread(&App::startGl, this);
	runCoreLoop();
	glThread.join();
}

void App::runCoreLoop() {
	Time time = Time();
	double totalTime = 0;
	while (running) {
		double lapsTime = time.getLapsTime();
		totalTime += lapsTime;
		if (totalTime >= gameUpdate) {
			totalTime = 0;
			updateGame();
		}
	}
}

void App::updateGame() {
	renderer.updateObjsToRender(objs);
}

void App::startGl() {
	renderer.initGlWindow();
	renderer.start();
}

void App::changeInputListenner(InputListenner *listenner) {
	renderer.setInputListenner(listenner);
}

void App::addObj(GameObject *obj) {
	objs.push_back(obj);
}