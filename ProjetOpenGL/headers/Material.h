#pragma once

#ifndef Material_H
#define Material_H

typedef struct {
	float ambient[3];
	float diffuse[3];
	float specular[3];
	float shininess;
} Material;

#endif