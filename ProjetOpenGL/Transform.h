#pragma once


typedef struct {
	float x;
	float y;
	float z;
} vec3;

typedef struct {
	float x;
	float y;
	float z;
	float theta;
} vec4Rot;

class Transform {

private:
	// Vecteur 3
	vec3 translation;
	// Vecteur 4
	vec4Rot rotation;
	// Vecteur 3
	vec3 scale;

public:
	Transform(vec3 t, vec4Rot r, vec3 s) : translation(t), rotation(r), scale(s) {}

	void setTranslation(vec3 translation);
	vec3 getTranslation();

	void setRotation(vec4Rot rotation);
	vec4Rot getRotation();

	void setScale(vec3 scale);
	vec3 getScale();

	float* getWorldMatrix();
};