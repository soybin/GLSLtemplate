#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include "shader.h"

std::string shader::parseShader(const char* dir) {
  std::ifstream file(dir);
  std::string line, ret = "";
    
  for (; std::getline(file, line); ret += '\n') {
    ret += line;
  }
    
  return ret;
}

int shader::compileShader(unsigned int type, const char* src) {
  unsigned int id = glCreateShader(type);
  glShaderSource(id, 1, &src, nullptr);
  glCompileShader(id);

  // check if it compiled
  int res;
  glGetShaderiv(id, GL_COMPILE_STATUS, &res);
  if (res) {
    return id;
  }

  // compilation failed. exception handling
  int len;
  glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
  char* message = (char*)alloca(len * sizeof(char));
  glGetShaderInfoLog(id, len, &len, message);
  std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader:" << std::endl << message << std::endl;
    
  return -1;
}

int shader::getUniformLocation(const char* name) {
  if (uniformMap.find(name) != uniformMap.end()) {
    return uniformMap[name];
  }

  unsigned int location = glGetUniformLocation(shaderID, name);

  if (location == -1) {
    return -1;
  }

  uniformMap[name] = location;
    
  return location;
}

shader::shader(std::string vert, std::string frag) {
	std::string strv;
	if (vert.size()) strv = parseShader(vert.c_str());
  std::string strf = parseShader(frag.c_str());

  unsigned int program = glCreateProgram();
  unsigned int vs;
	if (vert.size()) vs = compileShader(GL_VERTEX_SHADER, strv.c_str());
  unsigned int fs = compileShader(GL_FRAGMENT_SHADER, strf.c_str());

  if (vert.size()) glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);
  glValidateProgram(program);

  if (vert.size()) glDeleteShader(vs);
  glDeleteShader(fs);

  glUseProgram(program);

  shaderID = program;
}

shader::~shader() {
  glUseProgram(0);
  glDeleteProgram(shaderID);
}

void shader::bind() {
	glUseProgram(shaderID);
}

void shader::set1i(const char* name, int v) {
  glUniform1i(getUniformLocation(name), v);
}

void shader::set2i(const char* name, int v1, int v2) {
  glUniform2i(getUniformLocation(name), v1, v2);
}

void shader::set3i(const char* name, int v1, int v2, int v3) {
  glUniform3i(getUniformLocation(name), v1, v2, v3);
}

void shader::set4i(const char* name, int v1, int v2, int v3, int v4) {
  glUniform4i(getUniformLocation(name), v1, v2, v3, v4);
}

void shader::set1f(const char* name, float v) {
  glUniform1f(getUniformLocation(name), v);
}

void shader::set2f(const char* name, float v1, float v2) {
  glUniform2f(getUniformLocation(name), v1, v2);
}

void shader::set3f(const char* name, float v1, float v2, float v3) {
  glUniform3f(getUniformLocation(name), v1, v2, v3);
}

void shader::set4f(const char* name, float v1, float v2, float v3, float v4) {
  glUniform4f(getUniformLocation(name), v1, v2, v3, v4);
}
