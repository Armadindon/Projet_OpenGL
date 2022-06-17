#pragma once

#ifndef _Material_H_
#define _Material_H_

typedef struct {
	float *ambient;
	float *diffuse;
	float *specular;
	float shininess;
} Material;

#endif