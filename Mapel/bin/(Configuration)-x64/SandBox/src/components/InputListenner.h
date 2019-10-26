#pragma once
#include "../../dependencies/glew-2.1.0/include/GL/glew.h"
#include "../../dependencies/openGl/include/GLFW/glfw3.h"
#include <stdio.h>
#include "../components/Component.h"
#include <functional>
#include <iostream>
#include <vector>
#include <thread>

class Event {
private:
	std::function<void()> func;
	char key = 0;
	int param = 0;
public:
	Event() {}
	~Event() {}

	template<typename object, typename function>
	Event(object obj, function thefunc, char key, int param) {
		void (object::*functionsHolder) (void) = thefunc;
		this->func = std::bind(functionsHolder, obj);
		this->key = key;
		this->param = param;
	}

	int operator == (Event event) {
		if(this->key == event.key && this->param == event.param && this->func.target_type() == event.func.target_type()) {
			return 1;
		}
		return 0;
	}

	void fireFunc() {
		func();
	}

	// add multi threading later
	void testsEvent(GLFWwindow *wind) {
		if (glfwGetKey(wind, key) == param) {
			this->func();
		}
	}

};


class InputListenner{
private:
	int nbKeyListenner = 0;
	std::vector<Event> events;
	std::vector<std::thread> threads;

public:
	InputListenner(int nbKeyListenners);
	InputListenner();
	~InputListenner();
	
	// remove useless code!
	std::function<void()> bobHolder;
	void printBob();

	void addEvent(Event);

	void removeEvent(Event);

	int getNbKeyListenners();

	// return if event happend
	int checkEvent(Event);
	
	void checkFirerEvent(Event);

	void checkEvents(GLFWwindow *);
};