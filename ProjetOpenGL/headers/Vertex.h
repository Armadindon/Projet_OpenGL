#pragma once

#ifndef _Vertex_H_
#define _Vertex_H_

#include "Material.h"

#include <cstdint>
#include <utility>

struct Color {
	uint8_t r, g, b, a;
};


/* Struct Utilitaire pour un vecteur 4 représentant une vertex */
struct Vertex
{
	float position[3]; // x, y, z 
	float normal[3]; // nx, ny, ny
	float uv[2]; // u, v
};

typedef std::pair<Vertex, int> Vpair;

//CF https://stackoverflow.com/questions/14396788/how-can-i-generate-indices-from-vertex-list-in-linear-time

struct CmpClass // class comparing vertices in the set
{
    bool operator() (const Vpair& p1, const Vpair& p2) const
    {
        if (fabs(p1.first.position[0] - p2.first.position[0]) > 0.001f) return p1.first.position[0] < p2.first.position[0];
        if (fabs(p1.first.position[1] - p2.first.position[1]) > 0.001f) return p1.first.position[1] < p2.first.position[1];
        if (fabs(p1.first.position[2] - p1.first.position[2]) > 0.001f) return p1.first.position[1] < p2.first.position[2];
        if (fabs(p1.first.normal[0] - p2.first.normal[0]) > 0.001f) return p1.first.normal[0] < p2.first.normal[0];
        if (fabs(p1.first.normal[1] - p2.first.normal[1]) > 0.001f) return p1.first.normal[1] < p2.first.normal[1];
        if (fabs(p1.first.normal[2] - p1.first.normal[2]) > 0.001f) return p1.first.normal[1] < p2.first.normal[2];
        if (fabs(p1.first.uv[0] - p2.first.uv[0]) > 0.001f) return p1.first.uv[0] < p2.first.uv[0];
        if (fabs(p1.first.uv[1] - p2.first.uv[1]) > 0.001f) return p1.first.uv[1] < p2.first.uv[1];
        return false;
    }
};



#endif