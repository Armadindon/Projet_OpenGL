#pragma once

#define _USE_MATH_DEFINES

#include "Vertex.h"
#include "Triangle.h"
#include "Transform.h"
#include "GL/glew.h"
#include "../common/GLShader.h"
#include "../common/tiny_obj_loader.h"
#include "Material.h"

#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <iostream>

class Object3D
{
private:
	//Render
	GLuint VBO, VAO;
	GLShader shader;

	//Data
	Transform position;
	std::vector<Vertex> vertices;
	float *color;

	void clear();

public:
	Object3D() : VAO(0), VBO(0) { };
	Object3D(const char* model, const char* materialFolder, GLShader shader, Transform tf, float *color);
	void init();
	void loadObjFile(const char* filePath, const char* materialFolder);
	void render(GLFWwindow* window);
};

