#include "Matrix.h"
#include <math.h> 

// Fichier utilitaire pour regrouper toutes les fonctions liées aux matrices

float* getTranslationMatrix(float translationX, float translationY, float translationZ) {
	static float translationMatrix[16] = {
		1.f, 0.f, 0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		translationX, translationY, translationZ, 1.f
	};

	return translationMatrix;
}

float* getRotationMatrix(float Rx, float Ry, float Rz, float theta) {
	static float rotationMatrix[16] = {
		cosf(theta) + powf(Rx, 2) * (1 - cosf(theta)), Ry * Rx * (1 - cosf(theta)) + Rz * sinf(theta), Rz * Rx * (1 - cosf(theta)) - Ry * sin(theta), 0.f,
		Rx * Ry * (1 - cosf(theta)) - Rz * sinf(theta), cosf(theta) + powf(Ry, 2) * (1 - cosf(theta)), Rz * Ry * (1 - cosf(theta)) + Rx * sinf(theta), 0.f,
		Rx * Rz * (1 - cosf(theta)) + Ry * sinf(theta), Ry * Rz * (1 - cosf(theta)) - Rx * sinf(theta), cosf(theta) + powf(Rz, 2) * (1 - cosf(theta)), 0.f,
		0.f, 0.f, 0.f, 1.f
	};

	return rotationMatrix;
}

float* getScaleMatrix(float scaleX, float scaleY, float scaleZ) {
	static float scaleMatrix[16] = {
		scaleX, 0.f, 0.f, 0.f,
		0.f, scaleY, 0.f, 0.f,
		0.f, 0.f, scaleZ, 0.f,
		0.f, 0.f, 0.f, 1.f
	};

	return scaleMatrix;
}