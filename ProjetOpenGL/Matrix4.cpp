#include "Matrix4.h"
#include <iostream>
#include <vector>
#include <iterator>
#include <string>


using std::vector; using std::copy;

Matrix4::Matrix4(float* value) {
	matrix = (float*)malloc(sizeof(float) * 16);
	copy(value[0], value[15], matrix[0]);
}

Matrix4::~Matrix4()
{
	free(matrix);
}

float* Matrix4::getMatrixValue() {
	return matrix;
}

void Matrix4::setMatrixValue(float* value) {
	copy(value[0], value[15], matrix[0]);
}

Matrix4 Matrix4::getTranslationMatrix(float translationX, float translationY, float translationZ) {
	float translationMatrixStatic[16] = {
		1.f, 0.f, 0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		translationX, translationY, translationZ, 1.f
	};

	return Matrix4(translationMatrixStatic);
}

Matrix4 Matrix4::getRotationMatrix(float Rx, float Ry, float Rz, float theta)
{
	float rotationMatrixStatic[16] = {
		   cosf(theta) + powf(Rx, 2) * (1 - cosf(theta)), Ry * Rx * (1 - cosf(theta)) + Rz * sinf(theta), Rz * Rx * (1 - cosf(theta)) - Ry * sin(theta), 0.f,
		   Rx * Ry * (1 - cosf(theta)) - Rz * sinf(theta), cosf(theta) + powf(Ry, 2) * (1 - cosf(theta)), Rz * Ry * (1 - cosf(theta)) + Rx * sinf(theta), 0.f,
		   Rx * Rz * (1 - cosf(theta)) + Ry * sinf(theta), Ry * Rz * (1 - cosf(theta)) - Rx * sinf(theta), cosf(theta) + powf(Rz, 2) * (1 - cosf(theta)), 0.f,
		   0.f, 0.f, 0.f, 1.f
	};

	return Matrix4(rotationMatrixStatic);
}

Matrix4 Matrix4::getScaleMatrix(float scaleX, float scaleY, float scaleZ)
{
	float scaleMatrixStatic[16] = {
		   scaleX, 0.f, 0.f, 0.f,
		   0.f, scaleY, 0.f, 0.f,
		   0.f, 0.f, scaleZ, 0.f,
		   0.f, 0.f, 0.f, 1.f
	};

	return Matrix4(scaleMatrixStatic);
}

Matrix4 Matrix4::getProjectionMatrix(float zNear, float zFar, float aspect, float f)
{
	float projectionMatrixStatic[16] = {
		   f / aspect, 0.f, 0.f, 0.f,
		   0.f, f, 0.f, 0.f,
		   0.f, 0.f, ((zFar + zNear) / (zNear - zFar)), -1.f,
		   0.f, 0.f, ((2 * zNear * zFar) / (zNear - zFar)), 0.f
	};

	return Matrix4(projectionMatrixStatic);
}
