#include "headers/Camera.h"

vec4Rot* lookAt(vec3 eye, vec3 at, vec3 up) {
	vec3 zaxis = normalize({at.x - eye.x, at.y - eye.y, at.z - eye.z});
	vec3 xaxis = normalize(cross(zaxis, up));
	vec3 yaxis = cross(xaxis, zaxis);

	vec4Rot viewMatrix[4] = {
		{xaxis.x, xaxis.y, xaxis.z, -dot(xaxis, eye)},
		{yaxis.x, yaxis.y, yaxis.z, -dot(yaxis, eye)},
		{zaxis.x, zaxis.y, zaxis.z, -dot(zaxis, eye)},
		{0, 0, 0, 1}
	};

	return viewMatrix;
}
