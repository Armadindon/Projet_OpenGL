#pragma once

#ifndef Object3D_H
#define Object3D_H

#define _USE_MATH_DEFINES

#include "Vertex.h"
#include "Triangle.h"
#include "Transform.h"
#include "GL/glew.h"
#include "../../common/GLShader.h"
#include "../../common/tiny_obj_loader.h"
#include "../../common/toolsbox.h"
#include "Material.h"
#include "Light.h"
#include "Matrix.h"
#include "../Camera.h"

#include <GLFW/glfw3.h>
#include <vector>
#include <stdlib.h>
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
	AmbiantLight ambiantLight;
	DiffuseLight diffuseLight;
	SpecularLight specularLight;
	Material mat;
	Camera camera;

	void clear();

public:
	Object3D() : VAO(0), VBO(0) 
	{
		this->camera = Camera();
	}
	Object3D(const char* model, const char* materialFolder, GLShader shader, Transform tf, AmbiantLight ambiantLight, DiffuseLight diffuseLight, SpecularLight specularLight, float *color, Camera cam);
	void init();
	void loadObjFile(const char* filePath, const char* materialFolder);
	void render(GLFWwindow* window);
};

#endif