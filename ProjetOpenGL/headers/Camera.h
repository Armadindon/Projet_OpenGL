#pragma once

#ifndef Camera_H
#define Camera_H

#include "Vertex.h"

enum Movements {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

class Camera {

private:
	vec3 position;
	vec3 front, up, right;
	float speed;

public:
	Camera() : position({ 0.f, 0.f, 0.f }), front({ 0.f, 0.f, 0.f }), up({ 0.f, 0.f, 0.f }), right({ 0.f, 0.f, 0.f }) 
	{
		speed = 3.f;
	};

	Camera(vec3 position, vec3 front, vec3 up, vec3 right) : position(position), front(front), up(up), right(right)
	{
		speed = 3.f;
	};

	float* getViewMatrix();
	float* lookAt(vec3 eye, vec3 at, vec3 up);
};

#endif