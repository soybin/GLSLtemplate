#pragma once

#include <GLFW/glfw3.h>
#include "shader.h"

class engine {
	private:
		unsigned int width;
		unsigned int height;
		unsigned int vao;
		unsigned int vbo;
		unsigned int frames;
		shader* shMain;
		GLFWwindow* window;
		bool initGLFW();
		bool initGLEW();
		void loadModel();
	public:
		bool run;
		engine();
		~engine();
		void work();
};
