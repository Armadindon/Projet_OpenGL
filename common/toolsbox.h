#pragma once

#include <cstdint>

void MatrixMultiply(const float(&Matrix1)[16], const  float(&Matrix2)[16], float(&Matrix3)[16]);
void MatrixTranspose(const float(&MatrixIn)[16], float(&MatrixOut)[16]);
float MatrixDet4(const float(&Matrix)[16]);
float MatrixDet3(const float(&Matrix)[9]);
bool inverse(const float(&MatrixIn)[16], float(&MatrixOut)[16]);
bool convert(const float(&MatrixIn)[16], float(&MatrixOut)[16]);