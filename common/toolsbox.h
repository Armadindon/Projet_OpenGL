#pragma once
#ifndef Toolbox_H
#define Toolbox_H
#define _USE_MATH_DEFINES
#include <math.h>
#include <cstdint>

void MatrixMultiply(const float* Matrix1, const float* Matrix2, float* Matrix3);
void MatrixTranspose(const float* MatrixIn, float* MatrixOut);
float MatrixDet4(const float* Matrix);
float MatrixDet3(const float* Matrix);
bool inverseMatrix(const float* MatrixIn, float* MatrixOut);
float toRadians(float degrees);

#endif