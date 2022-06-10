#include "Transform.h"

#include "../common/toolsbox.h"
#include "Matrix.h"

void Transform::setTranslation(vec3 translation)
{
	this->translation = translation;
}

vec3 Transform::getTranslation()
{
	return this->translation;
}

void Transform::setRotation(vec4Rot rotation)
{
	this->rotation = rotation;
}

vec4Rot Transform::getRotation()
{
	return this->rotation;
}

void Transform::setScale(vec3 scale)
{
	this->scale = scale;
}

vec3 Transform::getScale()
{
	return this->scale;
}

float* Transform::getWorldMatrix()
{
	const float* translationMatrix = getTranslationMatrix(this->translation.x, this->translation.y, this->translation.z);
	const float* rotationMatrix = getRotationMatrix(this->rotation.x, this->rotation.y, this->rotation.z, this->rotation.theta);
	const float* scaleMatrix = getScaleMatrix(this->scale.x, this->scale.y, this->scale.z);

	float result[16];
	
	MatrixMultiply((float(&)[16]) translationMatrix, (float(&)[16]) rotationMatrix, result);
	MatrixMultiply(result, (float (&)[16]) scaleMatrix, result);
	
	return result;
}
