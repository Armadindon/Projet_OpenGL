#pragma once
#include <cmath>

struct vec2 {
	float x, y;
};

struct vec3 {
	float x, y, z;
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