#pragma once

#ifndef _Camera_H_
#define _Camera_H_

#include "../headers/Vertex.h"
#include "../headers/Vector.h"
#include "../headers/Matrix.h"
#include "../headers/Matrix4.h"

#include <GLFW/glfw3.h>

class Camera {

private:
	vec3 position, front, up;
	float speed, sensitivity, yaw, pitch;
	double lastFrame, mouseLastX, mouseLastY;
	bool firstMouse;

public:
	Camera() : position({ 0.f, 0.f, 0.f }), front({ 0.f, 0.f, -1.f }), up({ 0.f, 0.f, 0.f }), speed(0.f), sensitivity(0.f), yaw(-90.f), pitch(0), firstMouse(true) {
		this->lastFrame = glfwGetTime();
		// Set en dur de manière crara, on connait pas la taille de la fenetre
		this->mouseLastX = 640;
		this->mouseLastY = 360;
	};

	Camera(vec3 position, vec3 front, vec3 up, GLFWwindow* window) : position(position), front(front), up(up), yaw(-90.f), pitch(0), firstMouse(true)
	{
		sensitivity = .1f;
		speed = 3.f;
		this->lastFrame = glfwGetTime();
		int width, height;

		//On récupère la taille
		glfwGetWindowSize(window, &width, &height);
		this->mouseLastX = width / 2;
		this->mouseLastY = height / 2;
	};

	Matrix4 getLookAtMatrix();
	void processInput(GLFWwindow* window);
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	const vec3 getPosition();
};

#endif