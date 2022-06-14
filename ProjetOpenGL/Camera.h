#pragma once

#ifndef Camera_H
#define Camera_H

#include "headers/Vertex.h"
#include "headers/Vector.h"

#define _USE_MATH_DEFINES // for C++
#include <math.h>

class Camera {

private:
	vec3 position;
	vec3 target;
	vec3 front;
	vec3 up, right;
	float speed;

public:
	Camera() : position({ 0.f, 0.f, 0.f }), target({ 0.f, 0.f, 0.f }), up({ 0.f, 0.f, 0.f }), right({ 0.f, 0.f, 0.f }), front({ 0.f, 0.f, 0.f }), speed(10.f)
	{
		updateCameraVectors();
	};

	Camera(vec3 position, vec3 target, vec3 up) : position(position), target(target), up(up)
	{
		this->front = { 0.f, 0.f, 0.f };
		this->right = { 0.f, 0.f, 0.f };
		this->speed = 10.f;
		updateCameraVectors();
	};

	float* getLookAtMatrix();

	void ProcessKeyboard(int dir, float deltaTime)
	{
		float velocity = speed * deltaTime;
		vec3 front_v = { front.x * velocity, front.y * velocity, front.z * velocity };
		vec3 right_v = { right.x * velocity, right.y * velocity, right.z * velocity };
		if (dir == 1)
			position = { position.x + front_v.x, position.y + front_v.y, position.z + front_v.z };
		if (dir == 2)
			position -= front * velocity;
		if (dir == 3)
			position -= right * velocity;
		if (dir == 4)
			position += right * velocity;
	}

	void updateCameraVectors()
	{
		// calculate the new Front vector
		vec3 f;
		f.x = cosf(-90.f * (180.f / M_PI)) * cosf(0.f);
		f.y = sinf(0.f);
		f.z = sinf(-90.f * (180.f / M_PI)) * cosf(0.f);
		front = normalize(f);
		// also re-calculate the Right and Up vector
		right = normalize(cross(front, up));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		up =normalize(cross(right, front));
	}
};

#endif