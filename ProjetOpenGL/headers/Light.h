#pragma once

#ifndef _Light_H_
#define _Light_H_

typedef struct {
    float* position;

    float* ambientColor;
    float* diffuseColor;
    float* specularColor;
} LightParams;

#endif 