#pragma once
#include <cmath>

struct vec2 {
	float x, y;
};

struct vec3 {
	float x, y, z;

	vec3() : x(0.f), y(0.f), z(0.f) {};
	vec3(float x, float y, float z) : x(x), y(y), z(z) { };

	vec3 operator+ (vec3 vec2) {

		return vec3(this->x + vec2.x, this->y + vec2.y, this->z + vec2.z);
	}

	vec3 operator* (float n) {
		return vec3(this->x * n, this->y * n, this->z * n);
	}

	vec3& operator+= (vec3 vec) {
		this->x += vec.x;
		this->y += vec.y;
		this->z += vec.z;

		return *this;
	}

	vec3& operator-= (vec3 vec) {
		this->x -= vec.x;
		this->y -= vec.y;
		this->z -= vec.z;

		return *this;
	}

	float* toArray() {
		float* vec = (float*) malloc(sizeof(float) * 3);
		vec[0] = this->x;
		vec[1] = this->y;
		vec[2] = this->z;

		return vec;
	}
};

struct vec4Rot {
	float x;
	float y;
	float z;
	float theta;
};

float length(vec3 vector);
vec3 normalize(vec3 vector);
vec3 cross(vec3 vectorA, vec3 vectorB);