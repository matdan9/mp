#include "InputListenner.h"

InputListenner::InputListenner(int length){
	printf("init InputListenner!!");
	nbKeyListenner = length;
}

InputListenner::InputListenner() {
	
}

InputListenner::~InputListenner() {

}

void InputListenner::printBob() {
	printf("\nHELLO BIG BOB\n");
}

void InputListenner::removeEvent(Event event) {
	
}

int InputListenner::getNbKeyListenners() {
	return nbKeyListenner;
}

int InputListenner::checkEvent(Event event) {
	return 0;
}

void InputListenner::checkFirerEvent(Event event) {
		
}

void InputListenner::addEvent(Event event) {
	events.push_back(event);
	++nbKeyListenner;
}

void InputListenner::checkEvents(GLFWwindow *window) {
	for (int i = 0; i < nbKeyListenner; ++i) {
		events[i].testsEvent(window);
	}
}