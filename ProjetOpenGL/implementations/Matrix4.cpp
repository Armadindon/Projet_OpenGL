#include "../headers/Matrix4.h"
#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>    // std::swap
#include "../../common/toolsbox.h"

using std::vector; using std::copy;

Matrix4::Matrix4(float* value) {
	this->matrix = new float[16];

	// On copie les données dans la matrice
	for (int i = 0; i < 16;i++) {
		this->matrix[i] = value[i];
	}
}

Matrix4::Matrix4(Matrix4 const& other) : Matrix4(other.matrix) { }

Matrix4& Matrix4::operator=(Matrix4 other)
{
	swap(other);
	return *this;
}

void Matrix4::swap(Matrix4& m) {
	std::swap(this->matrix, m.matrix);
}

Matrix4::~Matrix4()
{
	delete[] this->matrix;
}

float* Matrix4::getMatrixValue() {
	return this->matrix;
}

void Matrix4::setMatrixValue(float* value) {
	for (int i = 0; i < 16;i++) {
		this->matrix[i] = value[i];
	}
}

Matrix4 Matrix4::inverse()
{
	float* inversed = new float[16];
	inverseMatrix(this->matrix, inversed);

	//On libère l'ancienne matrice et on set les nouvelles valeurs
	delete[] this->matrix;
	this->matrix = inversed;

	//On renvoie la matrice
	return *this;
}

Matrix4 Matrix4::transpose()
{
	float* transposed = new float[16];
	MatrixTranspose(this->matrix, transposed);

	//On libère l'ancienne matrice et on set les nouvelles valeurs
	delete[] this->matrix;
	this->matrix = transposed;

	//On renvoie la matrice
	return *this;
}

Matrix4 Matrix4::operator*(Matrix4 mat)
{
	float* mutliplied = new float[16];

	//On fait la mutliplication
	MatrixMultiply(this->matrix, mat.matrix, mutliplied);

	//On envoie le résultat en effaçant le tableau préalablement recopié dans le constructeur
	Matrix4 result = Matrix4(mutliplied);
	delete[] mutliplied;

	return result;
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
