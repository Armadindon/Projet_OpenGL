#include "headers/Vertex.h"
#include <tgmath.h>

vec3 normalize(vec3 vec) {
	float abs = sqrtf((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));

	return {vec.x/abs, vec.y/abs, vec.z/abs};
}

float dot(vec3 a, vec3 b) {
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

vec3 cross(vec3 a, vec3 b) {
	float x = (a.y * b.z) - (a.z - b.y);
	float y = (a.z * b.x) - (a.x * b.z);
	float z = (a.x * b.y) - (a.y * b.x);

	return { x, y, z };
}