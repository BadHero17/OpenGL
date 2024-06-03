#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Shader {
public: 
	unsigned int ID;
	  Shader(const char* vertexShaderPath, const char* fragmentShaderPath) {
		  std::string vertexShaderSrc, fragmentShaderSrc;
		  std::ifstream vertexShaderFile(vertexShaderPath,std::ios::in), fragmentShaderFile(fragmentShaderPath,std::ios::in);
		  vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		  fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		  try {
			  std::stringstream vertexShaderStream, fragmentShaderStream;
			  vertexShaderStream << vertexShaderFile.rdbuf();
			  fragmentShaderStream << fragmentShaderFile.rdbuf();
			  vertexShaderFile.close();
			  fragmentShaderFile.close();
			  vertexShaderSrc = vertexShaderStream.str();
			  fragmentShaderSrc = fragmentShaderStream.str();

		  }
		  catch (std::ifstream::failure e) {
			  std::cout << "Eroare la citirea shader-urilor" << std::endl;
		  }
		  const char* vertexShaderCode = vertexShaderSrc.c_str();
		  const char* fragmentShaderCode = fragmentShaderSrc.c_str();
		  //atribui shader-ul pentru vertice la un indice oarecare si il compilez

		  unsigned int vertexShader;
		  vertexShader = glCreateShader(GL_VERTEX_SHADER);
		  glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
		  glCompileShader(vertexShader);

		  //Debug la shader de vertice

		  int sw;
		  char Log[512];
		  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &sw);
		  if (!sw) {
			  glGetShaderInfoLog(vertexShader, 512, NULL, Log);
			  std::cout << "Eroare la vertexShader " << std::endl;
			  std::cout << Log << std::endl;
		  }

		  //Compile la shader de fragmente

		  unsigned int fragmentShader;
		  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		  glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
		  glCompileShader(fragmentShader);

		  //Debug la shader de fragmente

		  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &sw);
		  if (!sw) {
			  glGetShaderInfoLog(fragmentShader, 512, NULL, Log);
			  std::cout << "Eroare la fragmentShader " << std::endl;
			  std::cout << Log << std::endl;
		  }

		  ID = glCreateProgram();
		  glAttachShader(ID, vertexShader);
		  glAttachShader(ID, fragmentShader);
		  glLinkProgram(ID);

		  //Debug la program
		  glGetProgramiv(ID, GL_COMPILE_STATUS, &sw);
		  if (!sw) {
			  glGetProgramInfoLog(ID, 512, NULL, Log);
			  std::cout << "Eroare la Program " << std::endl;
			  std::cout << Log << std::endl;
		  }

		  //Sterge shader-urile, deja sunt inutile;
		  glDeleteShader(vertexShader);
		  glDeleteShader(fragmentShader);
	  }
	  void use() {
		  glUseProgram(ID);
	  }
	  void setBool(const std::string& name, bool value) {
		  glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	  }

	  void setInt(const std::string& name, int value) {
		  glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	  }
	  void setFloat(const std::string& name, float value) {
		  glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	  }
	  void setVec3(const std::string& name, glm::vec3 &value) {
		  glUniform3fv(glGetUniformLocation(ID, name.c_str()),1, &value[0]);
	  }
};
