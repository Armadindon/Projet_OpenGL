#pragma once

#include <cstdint>

void MatrixMultiply(const float* Matrix1, const float* Matrix2, float* Matrix3);
void MatrixTranspose(const float *MatrixIn, const float* MatrixOut);
float MatrixDet4(const float *Matrix);
float MatrixDet3(const float* Matrix);
bool inverse(const float* MatrixIn, const float* MatrixOut);
bool convert(const float* MatrixIn, const float* MatrixOut);