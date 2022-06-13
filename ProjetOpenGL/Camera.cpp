#include "headers/Camera.h"
#include <stdlib.h>


float* Camera::lookAt(vec3 eye, vec3 at, vec3 up) {
	vec3 zaxis = normalize({at.x - eye.x, at.y - eye.y, at.z - eye.z});
	vec3 xaxis = normalize(cross(zaxis, up));
	vec3 yaxis = cross(xaxis, zaxis);

	float* viewMatrix = (float*) malloc(sizeof(float) * 16);

	float staticViewMatrix[16] = {
		xaxis.x, xaxis.y, xaxis.z, -dot(xaxis, eye),
		yaxis.x, yaxis.y, yaxis.z, -dot(yaxis, eye),
		zaxis.x, zaxis.y, zaxis.z, -dot(zaxis, eye),
		0, 0, 0, 1
	};

	if (viewMatrix != NULL) {
		for (int i = 0; i < 16; i++)
			viewMatrix[i] = staticViewMatrix[i];
	}

	return viewMatrix;
}

float* Camera::getViewMatrix() {
	vec3 tmp = { this->position.x + this->front.x, this->position.y + this->front.y, this->position.z + this->front.z };

	return lookAt(this->position, tmp, this->up);
}
