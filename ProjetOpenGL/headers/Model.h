#pragma once

#ifndef _MODEL_H_
#define _MODEL_H_

#define _USE_MATH_DEFINES
#include <cmath>
#include <GL/glew.h>
#include <vector>
#include <iostream>

#include "../headers/Light.h"
#include "../headers/Matrix4.h"
#include "Camera.h"
#include "../../common/GLShader.h"
#include "../../common/tiny_obj_loader.h"
#include "../headers/Transform.h"

/* Classe de base de chaque modele 3D, prend le minimum pour le rendu */
class Model
{
protected:
	//Render
	GLuint VBO, VAO;
	GLShader shader;
	std::vector<Vertex> vertices;

	//Data
	Transform position;
	float* color;
	Camera* camera;

	virtual void init();
	virtual void loadObjFile(const char* filePath, const char* materialFolder);
	virtual void updateUniform(GLFWwindow* window);
	virtual void initAttribLocation();

public:
	Model() : VAO(0), VBO(0)
	{
		this->color = (float*) malloc(sizeof(float) * 3);
		if (this->color != nullptr) {
			this->color[0] = 0.f;
			this->color[1] = 0.f;
			this->color[2] = 0.f;
		}
		this->camera = new Camera();
	}
	Model(const char* model, const char* materialFolder, GLShader shader, Transform tf, float* color, Camera* cam);
	virtual void render(GLFWwindow* window);
	
};

#endif