#pragma once

#define TINYOBJLOADER_IMPLEMENTATION
#define _USE_MATH_DEFINES

#include "Vertex.h"
#include "Triangle.h"
#include "Transform.h"
#include "GL/glew.h"
#include "../common/GLShader.h"
#include "../common/tiny_obj_loader.h"

#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <iostream>

class Object3D
{
private:
	//Render
	GLuint VBO, IBO, VAO;
	GLShader shader;

	//Data
	Transform position;
	std::vector<Vertex> vertices;
	std::vector<Triangle> triangles;

	void clear();

public:
	void init();
	void loadObjFile(const char* filePath, const char* materialFolder);
	void render(GLFWwindow* window);
};

