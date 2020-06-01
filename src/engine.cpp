#include <iostream>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "engine.h"

float vertices[] = { 
	1.0f, 1.0f,
	-1.0f, 1.0f,
	1.0f, -1.0f,
	-1.0f, -1.0f,
	-1.0f, 1.0f,
	1.0f, -1.0f 
};

bool engine::initGLFW() {
	if (!glfwInit()) {
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	const GLFWvidmode* vMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	width = vMode->width;
	height = vMode->height;

	window = glfwCreateWindow(width, height, "glsl", glfwGetPrimaryMonitor(), 0);

	if (window == nullptr) {
		return false;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	return true;
}

bool engine::initGLEW() {
	return glewInit() == GLEW_OK;
}

void engine::loadModel() {
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
}

engine::engine() : frames(0), run(true) {

	if (!initGLFW()) {
		std::cout << "[-] Couldn't init GLFW." << std::endl;
		return;
	}

	if (!initGLEW()) {
		std::cout << "[-] Couldn't init GLEW." << std::endl;
		return;
	}

	//
	// quads don't have much depth to them
	//
	glDisable(GL_DEPTH_TEST);

	//
	// load them quads boi
	//
	loadModel();

	//
	// create shader object
	//
	shMain = new shader("main.vertex", "main.fragment");
	shMain->bind();

	//
	// set shader resolution
	//
	shMain->set2i("resolution", width, height);
}

engine::~engine() {
	// shader
	delete shMain;

	// glfwTerminate() handles window deletion
	glfwDestroyWindow(window);
	glfwTerminate();
}

void engine::work() {
	// frame count increment
	++frames;

	//
	// just in case you wanna exit your fabulous shader
	//
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) { 
		run = false;
	}

	// update number of frames gone by
	shMain->set1i("frames", frames);
	// update any other shader values as required
	// for example
	// 	shMain->set1i("uniform int", int);
	// 	shMain->set1f("uniform float", float);
	// 	shMain->set2i("uniform ivec2", int1, int2);
	// 	shMain->set3f("uniform vec3", float1, float2, float3);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//
	// new buffer and retrieve input
	//
	glfwSwapBuffers(window);
	glfwPollEvents();
}
