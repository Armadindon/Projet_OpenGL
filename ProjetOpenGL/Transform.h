#pragma once

typedef struct {
	float x;
	float y;
	float z;
} VEC3;

typedef struct {
	float x;
	float y;
	float z;
	float theta;
} VEC4ROT;

class Transform {

private:
	// Vecteur 3
	VEC3 translation;
	// Vecteur 4
	VEC4ROT rotation;
	// Vecteur 3
	VEC3 scale;

public:
	Transform() : translation({ 0.f, 0.f, 0.f }), rotation({ 0.f, 0.f, 0.f, 0.f }), scale({ 1.f, 1.f, 1.f }) {}
	Transform(VEC3 t, VEC4ROT r, VEC3 s) : translation(t), rotation(r), scale(s) {}

	void setTranslation(VEC3 translation);
	VEC3 getTranslation();

	void setRotation(VEC4ROT rotation);
	VEC4ROT getRotation();

	void setScale(VEC3 scale);
	VEC3 getScale();

	float* getWorldMatrix();
};