#pragma once
#include "Model.h"
#include "../stb/stb_image.h"

class ModelWithTexture : public Model
{
private:
	const char* fileToLoad;
	void loadTexture();

protected:
	GLuint textureID;
	void init() override;
	void initAttribLocation() override;
	void updateUniform(GLFWwindow* window) override;

public:
	ModelWithTexture() : Model(), textureID(0), fileToLoad("") { };
	ModelWithTexture(const char* model, const char* materialFolder, const char* textureToLoad, GLShader shader, Transform tf, float* color, Camera* cam);
	void render(GLFWwindow* window) override;
};

