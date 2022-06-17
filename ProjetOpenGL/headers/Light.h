#pragma once

#ifndef Light_H
#define Light_H

typedef struct {
    float position[3];

    float ambientColor[4];
    float diffuseColor[4];
    float specularColor[4];
} LightParams;

#endif 