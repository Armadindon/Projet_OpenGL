#pragma once

#ifndef _Vertex_H_
#define _Vertex_H_

#include "Material.h"

#include <cstdint>

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

#endif