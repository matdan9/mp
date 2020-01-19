#include "Renderer.h"

Renderer::Renderer(){}

Renderer::~Renderer(){
	glfwTerminate();
	//glDeleteShader(shader);
}

void Renderer::initGlWindow() {
	if (!glfwInit())
		return;
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(1920, 1080, "Hello World", NULL, NULL);
	glViewport(0, 0, 1920, 1080);
	//glfwSetFramebufferSizeCallback(window, resizeWindow);
	if (!window) {
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		printf("\n can not start glew \n");
	}
}

void Renderer::start() {
	addShaders();
	genVertexBuffer();
	genIndexBudder();
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 2, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	delete[] fragmentShader;
	delete[] vertexShader;
	run();
}

void Renderer::run() {
	while (!glfwWindowShouldClose(window)) {
		updateInput();
		render();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	this->~Renderer();
}

void Renderer::genIndexBudder() {
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 1000, NULL, GL_DYNAMIC_DRAW);
}

void Renderer::genVertexBuffer() {
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 1000, NULL, GL_DYNAMIC_DRAW);
}

void Renderer::updateInput() {
	inputListenner->checkEvents(this->window);
}

void Renderer::render() {
	if (objsToRender.size() <= 0) {
		return;
	}
	
	glClear(GL_COLOR_BUFFER_BIT);
	
	float *vPosition =  new float[8]{
		objsToRender.at(0)->position.getX(), 
		objsToRender.at(0)->position.getY(),

		objsToRender.at(0)->position.getX() + objsToRender.at(0)->dimention.getX(), 
		objsToRender.at(0)->position.getY(),

		objsToRender.at(0)->position.getX() + objsToRender.at(0)->dimention.getX(),
		objsToRender.at(0)->position.getY() + objsToRender.at(0)->dimention.getY(),

		objsToRender.at(0)->position.getX(),
		objsToRender.at(0)->position.getY() + objsToRender.at(0)->dimention.getY()
	};
	unsigned int *iBuffer = new unsigned int[6]{
		0, 1, 2,
		2, 3, 0
	};
	
	glNamedBufferSubData(vbo, 0, 8 * sizeof(*vPosition), vPosition);
	glNamedBufferSubData(ibo, 0, 6 * sizeof(*iBuffer), iBuffer);
	glDrawElements(GL_TRIANGLES, 6 * sizeof(*iBuffer), GL_UNSIGNED_INT, nullptr);

	delete[] vPosition;
	delete[] iBuffer;
}

void Renderer::addShaders() {
	loadShaders();
	std::string vs(vertexShader);
	std::string fs(fragmentShader);
	shader = createShader(vs, fs);
	glUseProgram(shader);
}

void Renderer::handelError(unsigned int shaderId) {
	int result;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
	if (!result) {
		int length = 0;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);
		char *errorMsg = (char*)_malloca(length * sizeof(char));
		glGetShaderInfoLog(shaderId, length, &length, errorMsg);
		std::cout << "can not copile shader" << std::endl;
		std::cout << errorMsg << std::endl;
	}
}

void Renderer::glClearError() {
	while (!glGetError());
}

bool Renderer::glCheckError() {
	while (GLenum error = glGetError()) {
		std::cout << "[opengl error] (" << error << ")" << std::endl;
		return false;
	}
}

unsigned int Renderer::compileShader(const std::string& source, unsigned int type) {
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	const int length[1] = {source.length()};
	glShaderSource(id, 1, &src, length);
	glCompileShader(id);
	handelError(id);
	return id;
}

unsigned int Renderer::createShader(const std::string& vertexShader, const std::string& fragmentShader) {
	printf("compiling shaders\n");
	unsigned int program = glCreateProgram();
	unsigned int vs = compileShader(vertexShader, GL_VERTEX_SHADER);
	unsigned int fs = compileShader(fragmentShader, GL_FRAGMENT_SHADER);
	printf("attach shaders\n");
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);
	printf("delete shaders\n");
	glDeleteShader(vs);
	glDeleteShader(fs);
	return program;
}

void Renderer::loadShaders() {
	FileManager fm = FileManager();
	if (vertexShader != nullptr) { delete[] vertexShader; }
	vsLength = fm.scanFile("../MapelEngine/src/shaders/vertexShader", &vertexShader);
	printf("loaded vertex loading fragment \n");
	if (fragmentShader != nullptr) { delete[] fragmentShader; }
	fsLength = fm.scanFile("../MapelEngine/src/shaders/fragmentShader", &fragmentShader);
	printf("loaded fragment \n");
}

void Renderer::resizeWindow(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

GLFWwindow* Renderer::getWindow() {
	return window;
}

void Renderer::setInputListenner(InputListenner *listenner) {
	delete inputListenner;
	inputListenner = listenner;
}

void Renderer::updateObjsToRender(std::vector<GameObject*> objs) {
	this->objsToRender = objs;
}

// https://learnopengl.com/Getting-started/Hello-Window
//https://www.youtube.com/watch?v=rSPkQzo5bfU&list=PLRwVmtr-pp06qT6ckboaOhnm9FxmzHpbY&index=23