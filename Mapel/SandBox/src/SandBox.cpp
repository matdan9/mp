#include "SanBox.h"

int main() {
	App app = App();
	InputListenner inputListenner = InputListenner();
	SandBox sandBox = SandBox();
	MVector *vec = new MVector(0.2, 0.2);
	Cube cube = Cube(&MVector(0,0), vec, 0.0001);

	Event* eventM = new Event(sandBox, &sandBox, &SandBox::printTest, ' ', 1);
	inputListenner.addEvent(*eventM);

	Event* eventN = new Event(sandBox, &sandBox, &SandBox::printTest, ' ', 1);
	inputListenner.addEvent(*eventN);

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

void SandBox::printTest() {
	++bob;
	printf("\n b = %d !!", bob);
}
/*
error because scope of Event() deletes copy of objClass and by the same de value of 
position and dimention in heap because of destroctor
	fix for no memory leaks and delete dimention and position remove object objClass of Event
	delete position and dekete dimention are commented in GameObject destroctor

refactor render
add fast tool for primary shape render

*/