#pragma once

#ifndef _Light_H_
#define _Light_H_

typedef struct {
    float position[3];

    float ambientColor[4];
    float diffuseColor[4];
    float specularColor[4];
} LightParams;

#endif 