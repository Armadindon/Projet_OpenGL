#include "headers/Matrix.h"
#include <math.h> 
#include <stdlib.h>


// Fichier utilitaire pour regrouper toutes les fonctions liées aux matrices


float* getTranslationMatrix(float translationX, float translationY, float translationZ) {
	float translationMatrixStatic[16] = {
		1.f, 0.f, 0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		translationX, translationY, translationZ, 1.f
	};

	float* translationMatrix = (float*)malloc(sizeof(float) * 16);
	if (translationMatrix != NULL) for (int i = 0; i < 16; i++) translationMatrix[i] = translationMatrixStatic[i];

	return translationMatrix;
}

float* getRotationMatrix(float Rx, float Ry, float Rz, float theta) {
	float rotationMatrixStatic[16] = {
		cosf(theta) + powf(Rx, 2) * (1 - cosf(theta)), Ry * Rx * (1 - cosf(theta)) + Rz * sinf(theta), Rz * Rx * (1 - cosf(theta)) - Ry * sin(theta), 0.f,
		Rx * Ry * (1 - cosf(theta)) - Rz * sinf(theta), cosf(theta) + powf(Ry, 2) * (1 - cosf(theta)), Rz * Ry * (1 - cosf(theta)) + Rx * sinf(theta), 0.f,
		Rx * Rz * (1 - cosf(theta)) + Ry * sinf(theta), Ry * Rz * (1 - cosf(theta)) - Rx * sinf(theta), cosf(theta) + powf(Rz, 2) * (1 - cosf(theta)), 0.f,
		0.f, 0.f, 0.f, 1.f
	};

	float* rotationMatrix = (float*)malloc(sizeof(float) * 16);
	if (rotationMatrix != NULL) for (int i = 0; i < 16; i++) rotationMatrix[i] = rotationMatrixStatic[i];

	return rotationMatrix;
}

float* getScaleMatrix(float scaleX, float scaleY, float scaleZ) {
	float scaleMatrixStatic[16] = {
		scaleX, 0.f, 0.f, 0.f,
		0.f, scaleY, 0.f, 0.f,
		0.f, 0.f, scaleZ, 0.f,
		0.f, 0.f, 0.f, 1.f
	};

	float* scaleMatrix = (float*)malloc(sizeof(float) * 16);
	if (scaleMatrix != NULL) for (int i = 0; i < 16; i++) scaleMatrix[i] = scaleMatrixStatic[i];

	return scaleMatrix;
}

float* getProjectionMatrix(float zNear, float zFar, float aspect, float f)
{
	const float projectionMatrixStatic[] = {
		f / aspect, 0.f, 0.f, 0.f,
		0.f, f, 0.f, 0.f,
		0.f, 0.f, ((zFar + zNear) / (zNear - zFar)), -1.f,
		0.f, 0.f, ((2 * zNear * zFar) / (zNear - zFar)), 0.f
	};

	float* projectionMatrix = (float*)malloc(sizeof(float) * 16);
	if (projectionMatrix != NULL) for (int i = 0; i < 16; i++) projectionMatrix[i] = projectionMatrixStatic[i];

	return projectionMatrix;
}

float* getLookAtMatrix(vec3 cameraPos, vec3 cameraTarget, vec3 up)
{
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

	float* lookAtMatrix = (float*)malloc(sizeof(float) * 16);
	MatrixMultiply(staticLookAtMatrix1, staticLookAtMatrix2, lookAtMatrix);

	return lookAtMatrix;
}
