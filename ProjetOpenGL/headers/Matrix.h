#pragma once
#ifndef Matrix_H
#define Matrix_H
#include "Vector.h"
#include "../../common/toolsbox.h"

float* getTranslationMatrix(float translationX, float translationY, float translationZ);
float* getRotationMatrix(float Rx, float Ry, float Rz, float theta);
float* getScaleMatrix(float scaleX, float scaleY, float scaleZ);
float* getProjectionMatrix(float zNear, float zFar, float aspect, float f);
float* getLookAtMatrix(vec3 cameraPos, vec3 cameraTarget, vec3 up);
#endif