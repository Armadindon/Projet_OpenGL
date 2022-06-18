#pragma once
#include "Model.h"
#include "../stb/stb_image.h"

class ModelWithCubemap : public Model
{
private:
	/* Juste pour stocker les fichiers utilisé */
	std::vector<std::string> textureFaces;
	void loadCubeMapTexture();

protected:
	GLuint textureID;
	void init() override;
	void initAttribLocation() override;
	void updateUniform(GLFWwindow* window) override;

public:
	ModelWithCubemap() : Model(), textureID(0) { };
	ModelWithCubemap(const char* model, const char* materialFolder, std::vector<std::string> cubemap, GLShader shader, Transform tf, float* color, Camera* cam);
	void render(GLFWwindow* window);
	void changeTexture(std::vector<std::string> textureFaces);
};

