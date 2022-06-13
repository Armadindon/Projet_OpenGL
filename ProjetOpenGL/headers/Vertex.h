#pragma once

#ifndef Vertex_H
#define Vertex_H

#include "Material.h"

#include <cstdint>

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

struct Color {
	uint8_t r, g, b, a;
};

/* Struct Utilitaire pour un vecteur 4 représentant une rotation */
struct Vertex
{
	float position[3]; // x, y, z 
	float normal[3]; // nx, ny, ny
	float uv[2]; // u, v
};

vec3 cross(vec3 a, vec3 b);
float dot(vec3 a, vec3 b);
vec3 normalize(vec3 vec);

#endif