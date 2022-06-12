#pragma once

#ifndef Light_H
#define Light_H

typedef struct {
	float color[4];
	float ambiantStrength;
} AmbiantLight;

typedef struct {
	float position[3];
} DiffuseLight;

#endif 