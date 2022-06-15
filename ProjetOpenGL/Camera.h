#pragma once

#ifndef Camera_H
#define Camera_H

#include "headers/Vertex.h"
#include "headers/Vector.h"
#include <GLFW/glfw3.h>

class Camera {

private:
	vec3 position;
	vec3 front;
	vec3 up;
	float speed;
	double lastFrame;

public:
	Camera() : position({ 0.f, 0.f, 0.f }), front({ 0.f, 0.f, -1.f }), up({ 0.f, 0.f, 0.f }), speed(0.f) {
		this->lastFrame = glfwGetTime();
	};

	Camera(vec3 position, vec3 front, vec3 up) : position(position), front(front), up(up)
	{
		speed = 3.f;
		this->lastFrame = glfwGetTime();
	};

	float* getLookAtMatrix();
	void processInput(GLFWwindow *window);
};

#endif