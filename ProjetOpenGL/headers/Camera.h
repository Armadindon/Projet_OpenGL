#pragma once

#ifndef Camera_H
#define Camera_H

#include "Vertex.h"

class Camera {

public:
	Camera() {};

	vec4Rot* lookAt(vec3 eye, vec3 at, vec3 up);
};

#endif