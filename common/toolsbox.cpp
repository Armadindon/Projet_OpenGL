#include "toolsbox.h"


void convert4(const float* MatrixIn, float* MatrixOut) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			MatrixOut[i * 4 + j] = MatrixIn[j * 4 + i];
		}
	}
}


void convert3(const float* MatrixIn, float* MatrixOut) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			MatrixOut[i * 3 + j] = MatrixIn[i + j * 3];
		}
	}
}

void MatrixMultiply(const float* Matrix1, const float* Matrix2, float* Matrix3) {
	float M1[16], M2[16], M3[16];
	convert4(Matrix1, M1);
	convert4(Matrix2, M2);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			float SumElements = 0.0f;
			for (int k = 0; k < 4; k++) {
				SumElements += M1[i * 4 + k] * M2[k * 4 + j];
			}
			M3[i * 4 + j] = SumElements;
		}
	}


	convert4(M3, Matrix3);
}

void MatrixTranspose(const float* MatrixIn, float* MatrixOut) {
	float MI[16], MO[16];
	convert4(MatrixIn, MI);
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			MO[j * 4 + i] = MI[i * 4 + j];
		}
	}
	convert4(MO, MatrixOut);
}


float MatrixDet4(const float* Matrix) {
	float M[16];
	convert4(Matrix, M);
	float a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, determinant;
	a = M[0 * 4 + 0];
	b = M[0 * 4 + 1];
	c = M[0 * 4 + 2];
	d = M[0 * 4 + 3];

	e = M[1 * 4 + 0];
	f = M[1 * 4 + 1];
	g = M[1 * 4 + 2];
	h = M[1 * 4 + 3];

	i = M[2 * 4 + 0];
	j = M[2 * 4 + 1];
	k = M[2 * 4 + 2];
	l = M[2 * 4 + 3];

	m = M[3 * 4 + 0];
	n = M[3 * 4 + 1];
	o = M[3 * 4 + 2];
	p = M[3 * 4 + 3];

	determinant = a * f * k * p - a * f * l * o - a * g * j * p + a * g * l * n + a * h * j * o - a * h * k * n - b * e * k * p + b * e * l * o + b * g * i * p - b * g * l * m - b * h * i * o + b * h * k * m + c * e * j * p - c * e * l * n - c * f * i * p + c * f * l * m + c * h * i * n - c * h * j * m - d * e * j * o + d * e * k * n + d * f * i * o - d * f * k * m - d * g * i * n + d * g * j * m;
	return determinant;

}

float MatrixDet3(const float* Matrix) {
	float a, b, c, d, e, f, g, h, i, j, k, l, determinant;
	float M[9];
	convert3(Matrix, M);

	a = M[0];
	b = M[1];
	c = M[2];

	d = M[1 * 3 + 0];
	e = M[1 * 3 + 1];
	f = M[1 * 3 + 2];

	g = M[2 * 3 + 0];
	h = M[2 * 3 + 1];
	i = M[2 * 3 + 2];


	determinant = a * (e * i - f * h) - b * (d * i - f * g) + c * (d * h - e * g);
	return determinant;

}

bool inverse(const float* MatrixIn, float* MatrixOut) {

	float MI[16], MO[16];
	convert4(MatrixIn, MI);
	double inv[16], det;
	int i;

	inv[0] = MI[5] * MI[10] * MI[15] -
		MI[5] * MI[11] * MI[14] -
		MI[9] * MI[6] * MI[15] +
		MI[9] * MI[7] * MI[14] +
		MI[13] * MI[6] * MI[11] -
		MI[13] * MI[7] * MI[10];

	inv[4] = -MI[4] * MI[10] * MI[15] +
		MI[4] * MI[11] * MI[14] +
		MI[8] * MI[6] * MI[15] -
		MI[8] * MI[7] * MI[14] -
		MI[12] * MI[6] * MI[11] +
		MI[12] * MI[7] * MI[10];

	inv[8] = MI[4] * MI[9] * MI[15] -
		MI[4] * MI[11] * MI[13] -
		MI[8] * MI[5] * MI[15] +
		MI[8] * MI[7] * MI[13] +
		MI[12] * MI[5] * MI[11] -
		MI[12] * MI[7] * MI[9];

	inv[12] = -MI[4] * MI[9] * MI[14] +
		MI[4] * MI[10] * MI[13] +
		MI[8] * MI[5] * MI[14] -
		MI[8] * MI[6] * MI[13] -
		MI[12] * MI[5] * MI[10] +
		MI[12] * MI[6] * MI[9];

	inv[1] = -MI[1] * MI[10] * MI[15] +
		MI[1] * MI[11] * MI[14] +
		MI[9] * MI[2] * MI[15] -
		MI[9] * MI[3] * MI[14] -
		MI[13] * MI[2] * MI[11] +
		MI[13] * MI[3] * MI[10];

	inv[5] = MI[0] * MI[10] * MI[15] -
		MI[0] * MI[11] * MI[14] -
		MI[8] * MI[2] * MI[15] +
		MI[8] * MI[3] * MI[14] +
		MI[12] * MI[2] * MI[11] -
		MI[12] * MI[3] * MI[10];

	inv[9] = -MI[0] * MI[9] * MI[15] +
		MI[0] * MI[11] * MI[13] +
		MI[8] * MI[1] * MI[15] -
		MI[8] * MI[3] * MI[13] -
		MI[12] * MI[1] * MI[11] +
		MI[12] * MI[3] * MI[9];

	inv[13] = MI[0] * MI[9] * MI[14] -
		MI[0] * MI[10] * MI[13] -
		MI[8] * MI[1] * MI[14] +
		MI[8] * MI[2] * MI[13] +
		MI[12] * MI[1] * MI[10] -
		MI[12] * MI[2] * MI[9];

	inv[2] = MI[1] * MI[6] * MI[15] -
		MI[1] * MI[7] * MI[14] -
		MI[5] * MI[2] * MI[15] +
		MI[5] * MI[3] * MI[14] +
		MI[13] * MI[2] * MI[7] -
		MI[13] * MI[3] * MI[6];

	inv[6] = -MI[0] * MI[6] * MI[15] +
		MI[0] * MI[7] * MI[14] +
		MI[4] * MI[2] * MI[15] -
		MI[4] * MI[3] * MI[14] -
		MI[12] * MI[2] * MI[7] +
		MI[12] * MI[3] * MI[6];

	inv[10] = MI[0] * MI[5] * MI[15] -
		MI[0] * MI[7] * MI[13] -
		MI[4] * MI[1] * MI[15] +
		MI[4] * MI[3] * MI[13] +
		MI[12] * MI[1] * MI[7] -
		MI[12] * MI[3] * MI[5];

	inv[14] = -MI[0] * MI[5] * MI[14] +
		MI[0] * MI[6] * MI[13] +
		MI[4] * MI[1] * MI[14] -
		MI[4] * MI[2] * MI[13] -
		MI[12] * MI[1] * MI[6] +
		MI[12] * MI[2] * MI[5];

	inv[3] = -MI[1] * MI[6] * MI[11] +
		MI[1] * MI[7] * MI[10] +
		MI[5] * MI[2] * MI[11] -
		MI[5] * MI[3] * MI[10] -
		MI[9] * MI[2] * MI[7] +
		MI[9] * MI[3] * MI[6];

	inv[7] = MI[0] * MI[6] * MI[11] -
		MI[0] * MI[7] * MI[10] -
		MI[4] * MI[2] * MI[11] +
		MI[4] * MI[3] * MI[10] +
		MI[8] * MI[2] * MI[7] -
		MI[8] * MI[3] * MI[6];

	inv[11] = -MI[0] * MI[5] * MI[11] +
		MI[0] * MI[7] * MI[9] +
		MI[4] * MI[1] * MI[11] -
		MI[4] * MI[3] * MI[9] -
		MI[8] * MI[1] * MI[7] +
		MI[8] * MI[3] * MI[5];

	inv[15] = MI[0] * MI[5] * MI[10] -
		MI[0] * MI[6] * MI[9] -
		MI[4] * MI[1] * MI[10] +
		MI[4] * MI[2] * MI[9] +
		MI[8] * MI[1] * MI[6] -
		MI[8] * MI[2] * MI[5];

	det = MI[0] * inv[0] + MI[1] * inv[4] + MI[2] * inv[8] + MI[3] * inv[12];

	if (det == 0)
		return false;

	det = 1.0 / det;

	for (i = 0; i < 16; i++)
		MO[i] = inv[i] * det;


	convert4(MO, MatrixOut);

	return true;
}

float toRadians(float degrees)
{
	return degrees * M_PI / 180;
}

