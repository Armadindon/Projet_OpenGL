#pragma once

#ifndef Camera_H
#define Camera_H

#include "headers/Vertex.h"
#include "headers/Vector.h"

enum Movements {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

class Camera {

private:
	vec3 position;
	vec3 target;
	vec3 up;
	float speed;

public:
	Camera() : position({ 0.f, 0.f, 0.f }), target({ 0.f, 0.f, 0.f }), up({ 0.f, 0.f, 0.f }), speed(0.f) {};

	Camera(vec3 position, vec3 target, vec3 up) : position(position), target(target), up(up)
	{
		speed = 3.f;
	};

	float* getLookAtMatrix();
};

#endif