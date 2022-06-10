#include "Transform.h"

#include "../common/toolsbox.h"
#include "Matrix.h"
#include <stdlib.h>

void Transform::setTranslation(VEC3 translation)
{
	this->translation = translation;
}

VEC3 Transform::getTranslation()
{
	return this->translation;
}

void Transform::setRotation(VEC4ROT rotation)
{
	this->rotation = rotation;
}

VEC4ROT Transform::getRotation()
{
	return this->rotation;
}

void Transform::setScale(VEC3 scale)
{
	this->scale = scale;
}

VEC3 Transform::getScale()
{
	return this->scale;
}

float* Transform::getWorldMatrix()
{
	const float* translationMatrix = getTranslationMatrix(this->translation.x, this->translation.y, this->translation.z);
	const float* rotationMatrix = getRotationMatrix(this->rotation.x, this->rotation.y, this->rotation.z, this->rotation.theta);
	const float* scaleMatrix = getScaleMatrix(this->scale.x, this->scale.y, this->scale.z);

	float* result = (float*)malloc(sizeof(float) * 16);
	float* worldMatrix = (float*)malloc(sizeof(float) * 16);

	MatrixMultiply(translationMatrix, rotationMatrix, result);
	MatrixMultiply(result, scaleMatrix, worldMatrix);

	return worldMatrix;
}
