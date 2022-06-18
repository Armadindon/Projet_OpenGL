#include "../headers/Transform.h"

#include "../headers/Matrix.h"
#include "../headers/Matrix4.h"
#include <stdlib.h>

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

Matrix4 Transform::getWorldMatrix()
{
	
	Matrix4 translationMatrix = Matrix4::getTranslationMatrix(this->translation.x, this->translation.y, this->translation.z);
	Matrix4 rotationMatrix = Matrix4::getRotationMatrix(this->rotation.x, this->rotation.y, this->rotation.z, this->rotation.theta);
	Matrix4 scaleMatrix = Matrix4::getScaleMatrix(this->scale.x, this->scale.y, this->scale.z);
	
	Matrix4 worldMatrix = translationMatrix * rotationMatrix * scaleMatrix;
	return worldMatrix;
}
