#include "Camera.h"
#include "headers/Matrix.h"

float* Camera::getLookAtMatrix()
{
	vec3 cameraPos = this->position;
	vec3 cameraTarget = this->target;
	vec3 up = this->up;

	vec3 cameraDirection = normalize({ cameraPos.x - cameraTarget.x, cameraPos.y - cameraTarget.y, cameraPos.z - cameraTarget.z });
	vec3 cameraRight = normalize(cross(up, cameraDirection));
	vec3 cameraUp = cross(cameraDirection, cameraRight);

	float staticLookAtMatrix1[] = {
		cameraRight.x, cameraUp.x, cameraDirection.x, 0.f,
		cameraRight.y, cameraUp.y, cameraDirection.y, 0.f,
		cameraRight.z, cameraUp.z, cameraDirection.z, 0.f,
		0.f, 0.f, 0.f, 1.f
	};

	float staticLookAtMatrix2[] = {
		1.f, 0.f, 0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		-cameraPos.x, -cameraPos.y, -cameraPos.z, 1.f
	};

	float* lookAtMatrix = (float*) malloc(sizeof(float) * 16);
	MatrixMultiply(staticLookAtMatrix1, staticLookAtMatrix2, lookAtMatrix);

	return lookAtMatrix;
}