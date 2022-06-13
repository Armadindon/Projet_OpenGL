#pragma once

#ifndef Vertex_H
#define Vertex_H

#include "Material.h"

#include <cstdint>

typedef struct {
	float x, y;
} vec2;

typedef struct {
	float x, y, z;
} vec3;

typedef struct {
	float x;
	float y;
	float z;
	float theta;
} vec4Rot;

typedef struct {
	uint8_t r, g, b, a;
} Color;

/* Struct Utilitaire pour un vecteur 4 représentant une rotation */
typedef struct 
{
	float position[3]; // x, y, z 
	float normal[3]; // nx, ny, ny
	float uv[2]; // u, v
} Vertex;

vec3 cross(vec3 a, vec3 b);
float dot(vec3 a, vec3 b);
vec3 normalize(vec3 vec);

#endif