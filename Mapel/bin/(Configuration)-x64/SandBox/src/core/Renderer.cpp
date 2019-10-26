#include "Renderer.h"

void keyCallBack(GLFWwindow *window, int key, int scanCode, int action, int mods) {
	
}

Renderer::Renderer(){
	
}

Renderer::~Renderer(){
	glfwTerminate();
}

void Renderer::handelError(unsigned int shaderId) {
	int result;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
	if (!result) {
		int length = 0;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);
		char *errorMsg = (char*)alloca(length * sizeof(char));
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

void Renderer::start() {
	loadShaders();
	std::string vs(vertexShader);
	std::string fs(fragmentShader);
	shader = createShader(vs, fs);
	glUseProgram(shader);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 18, vertices_position, GL_STATIC_DRAW);
	
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 12, indexBuffer, GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 2, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	run();
	delete[] fragmentShader;
	delete[] vertexShader;
}

void Renderer::initGlWindow() {
	/* Initialize the library */
	if (!glfwInit())
		return;
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1920, 1080, "Hello World", NULL, NULL);
	glViewport(0,0, 1920, 1080);
	//glfwSetFramebufferSizeCallback(window, resizeWindow);
	if (!window){
		glfwTerminate();
		return;
	}
	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		printf("\n can not start glew \n");
	}
}

void Renderer::run() {
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window)){

		//check for inputs
		inputListenner->checkEvents(this->window);
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, nullptr);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}
	glfwTerminate();
	glDeleteShader(shader);
	return;
}

GLFWwindow* Renderer::getWindow() {
	return window;
}

void Renderer::setInputListenner(InputListenner *listenner) {
	delete inputListenner;
	inputListenner = listenner;
}

// https://learnopengl.com/Getting-started/Hello-Window
// https://stackoverflow.com/questions/14316348/function-pointer-from-one-class-to-member-function-of-any-class
// https://stackoverflow.com/questions/13236124/how-to-implement-a-simplest-c-callable-object-wrapper
// https://stackoverflow.com/questions/610245/where-and-why-do-i-have-to-put-the-template-and-typename-keywords   http://www.cplusplus.com/reference/functional/function/
// http://timmurphy.org/2014/08/28/passing-member-functions-as-template-parameters-in-c/ IMPORTENT