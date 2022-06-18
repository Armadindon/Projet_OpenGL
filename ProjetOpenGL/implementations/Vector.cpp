#include "../headers/Vector.h"

float length(vec3 vector)
{
	return abs(sqrt((vector.x * vector.x) + (vector.y * vector.y) + (vector.z * vector.z)));
}

vec3 normalize(vec3 vector)
{
	float vecLength = length(vector);
	return { vector.x / vecLength, vector.y / vecLength, vector.z / vecLength };
}

vec3 cross(vec3 vectorA, vec3 vectorB)
{
	return { 
		vectorA.y * vectorB.z - vectorA.z * vectorB.y,
		vectorA.z * vectorB.x - vectorA.x * vectorB.z,
		vectorA.x * vectorB.y - vectorA.y * vectorB.x
	};
}
