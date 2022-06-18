#pragma once

#ifndef _Object3D_H_
#define _Object3D_H_

#define _USE_MATH_DEFINES

#include "Vertex.h"
#include "Triangle.h"
#include "Transform.h"
#include "GL/glew.h"
#include "../../common/GLShader.h"
#include "../../common/toolsbox.h"
#include "Material.h"
#include "Light.h"
#include "Model.h"
#include "Camera.h"
#include "Matrix4.h"

#include <GLFW/glfw3.h>
#include <vector>
#include <stdlib.h>
#include <math.h>
#include <iostream>

/* Classe 3D gérant les matériaux */
class ModelWithMat: public Model
{
protected:
	LightParams light;
	Material mat;
	void loadObjFile(const char* filePath, const char* materialFolder) override;
	void initAttribLocation() override;
	void updateUniform(GLFWwindow* window) override;


public:
	ModelWithMat() : Model(), light({ 0.f, 0.f, 0.f, 0.f }), mat({ nullptr, nullptr, nullptr, 0.f }) { };
	ModelWithMat(const char* model, const char* materialFolder, GLShader shader, Transform tf, LightParams light, float* color, Camera* cam);
	void setMaterial(Material mat);
};

#endif