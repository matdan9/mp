#pragma once
#define _CRT_SECURE_NO_DEPRECATE
#include "../../dependencies/glew-2.1.0/include/GL/glew.h"
#include "../../dependencies/openGl/include/GLFW/glfw3.h"
#include <stdio.h>
#include <iostream>
#include <string.h>
#include "../components/FileManager.h"
#include "../components/InputListenner.h"
#include <vector>
#include "GameObject.h"

#define ASSERT(x) if(!(x)) __debugbreak();

class Renderer {
private:
	InputListenner *inputListenner = new InputListenner();
	GLuint vbo;
	unsigned int ibo;
	GLFWwindow *window;
	float verticesPosition[18] = {
	0.0, 0.0,
	0.5, 0.0,
	0.5, 0.5,

	0.0, 0.5,
	-0.5, 0.5,

	-0.5, 0.0,
	-0.5,-0.5,

	0.0,-0.5,
	0.5,-0.5,
	};
	unsigned int indexBuffer[12] = {
		0, 1, 2,
		0, 3, 4,
		0, 5, 6,
		0, 7, 8
	};
	int vsLength;
	int fsLength;
	char* vertexShader = nullptr;
	char* fragmentShader = nullptr;
	unsigned int shader;
	std::vector<GameObject*> objsToRender;

	void glClearError();
	bool glCheckError();
	void handelError(unsigned int);
	void run();
	void resizeWindow(GLFWwindow* windoe, int width, int height);
	void addShaders();
	void updateInput();
	void render();
	void genVertexBuffer();
	void genIndexBudder();

public:
	Renderer();
	~Renderer();
	void loadShaders();
	unsigned int compileShader(const std::string& source, unsigned int type);
	unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);
	void start();
	void initGlWindow();

	void setInputListenner(InputListenner *);
	void updateObjsToRender(std::vector<GameObject*> objs);

	//change later for more security
	GLFWwindow* getWindow();
	InputListenner* getInputListenner() {
		return inputListenner;
	}
};

