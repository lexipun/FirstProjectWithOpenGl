#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
	unsigned int ID;

	Shader(const char* vertexPath, const char* fragmentPath);

	void use();

	void set(const std::string& name, bool value) const;
	void set(const std::string& name, float value) const;
	void set(const std::string& name, int value) const;
};

#endif 