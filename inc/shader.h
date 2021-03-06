#pragma once

#include <string>
#include <unordered_map>

class shader {
private:
  std::unordered_map<const char*, unsigned int> uniformMap;

  std::string parseShader(const char* dir);
  int compileShader(unsigned int type, const char* src);
  int getUniformLocation(const char* name);
public:
  unsigned int shaderID;
  shader(std::string vert, std::string frag);
  ~shader();

	// just bind it already boiiiiiiiii
	void bind();

  // uniform setters
  void set1i(const char* name, int v);
  void set2i(const char* name, int v1, int v2);
  void set3i(const char* name, int v1, int v2, int v3);
  void set4i(const char* name, int v1, int v2, int v3, int v4);
  void set1f(const char* name, float v);
  void set2f(const char* name, float v1, float v2);
  void set3f(const char* name, float v1, float v2, float v3);
  void set4f(const char* name, float v1, float v2, float v3, float v4);
};
