#pragma once

#ifndef Material_H
#define Material_H

typedef struct {
	float *ambient;
	float *diffuse;
	float *specular;
	float shininess;
} Material;

#endif