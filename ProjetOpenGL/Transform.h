#pragma once
#include "Vertex.h"

class Transform {

private:
	// Vecteur 3
	vec3 translation;
	// Vecteur 4
	vec4Rot rotation;
	// Vecteur 3
	vec3 scale;

public:
	Transform() : translation({ 0.f, 0.f, 0.f }), rotation({ 0.f, 0.f, 0.f, 0.f }), scale({ 1.f, 1.f, 1.f }) {}
	Transform(vec3 t, vec4Rot r, vec3 s) : translation(t), rotation(r), scale(s) {}

	void setTranslation(vec3 translation);
	vec3 getTranslation();

	void setRotation(vec4Rot rotation);
	vec4Rot getRotation();

	void setScale(vec3 scale);
	vec3 getScale();

	float* getWorldMatrix();
};