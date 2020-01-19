#include "SanBox.h"

int main() {
	App app = App();
	InputListenner inputListenner = InputListenner();
	SandBox sandBox = SandBox();
	Cube cube = Cube(MVector(0,0), MVector(0.2, 0.2), 0.0005);

	Event *eventd = new Event(cube, &cube, &Cube::moveRight, 'D', 1);
	inputListenner.addEvent(*eventd);
	
	Event *eventa = new Event(cube, &cube, &Cube::moveLeft, 'A', 1);
	inputListenner.addEvent(*eventa);
	
	Event *eventw = new Event(cube, &cube, &Cube::moveUp, 'W', 1);
	inputListenner.addEvent(*eventw);
	
	Event *events = new Event(cube, &cube, &Cube::moveDown, 'S', 1);
	inputListenner.addEvent(*events);
	
	app.changeInputListenner(&inputListenner);
	app.addObj(&cube);
	app.start();
	return 0;
}

SandBox::SandBox(){ 
	
}

SandBox::~SandBox(){

}
/*
refactor render
add fast tool for primary shape render
*/