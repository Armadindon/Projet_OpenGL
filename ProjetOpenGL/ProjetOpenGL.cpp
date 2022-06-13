
// seulement si glew32s.lib
#define GLEW_STATIC 1
#define TINYOBJLOADER_IMPLEMENTATION

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

#include "GL/glew.h"

#include <GLFW/glfw3.h>

#include "../common/GLShader.h"

#include "headers/Matrix.h"
#include "headers/Vertex.h"
#include "headers/Transform.h"
#include "headers/Object3D.h"
#include "headers/Light.h"


// attention, ce define ne doit etre specifie que dans 1 seul fichier cpp
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

GLShader modelShader, lightShader;


GLuint TexID;

Transform tf;

Object3D sphere, lightCube, cube;

//Paramètres globaux
float ligtCubeColor[] = { 1.f, 1.f, 1.f, 1.f };
float sphereColor[] = { 0.9882f, 0.7294f, 0.012f, 1.f };
float cubeColor[] = { 0.105f, 0.772f, 0.125f, 1.f };

float lightPose[] = { 0.f, 0.f, -10.f };

AmbiantLight ambiantLight = { { 1.f, 1.f, 1.f, 1.f }, 0.3f };
//Pour le moment, on ne gère qu'une diffuse light
DiffuseLight diffuseLight = { {lightPose[0], lightPose[1], lightPose[2]} };

SpecularLight specularLight = { 1.f };


void loadTexFromFile(const char* filename) {
	//On initialise la texture
	glGenTextures(1, &TexID);
	glBindTexture(GL_TEXTURE_2D, TexID);

	// Filtrage bilineaire dans tous les cas (Minification et Magnification)
	// les coordonnees de texture sont limitees a [0 ; 1[
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	int w, h;
	uint8_t* data = stbi_load(filename, &w, &h, nullptr, STBI_rgb_alpha);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);
	}
}

bool Initialise()
{
	GLenum ret = glewInit();

	modelShader.LoadVertexShader("shaders/3DModel.vert");
	modelShader.LoadFragmentShader("shaders/3DModel.frag");
	modelShader.Create();

	lightShader.LoadVertexShader("shaders/LightShader.vert");
	lightShader.LoadFragmentShader("shaders/LightShader.frag");
	lightShader.Create();

	//On active le test de profondeur et le face culling
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	Transform lightCubeTransform = Transform({ lightPose[0], lightPose[1], lightPose[2] }, { 0.f, 0.f, 0.f, 0.f }, { 1.f,1.f,1.f });
	lightCube = Object3D("../models/cube/cube.obj", "../models/cube", lightShader, lightCubeTransform, ambiantLight, diffuseLight, specularLight, ligtCubeColor);

	Transform sphereTransform = Transform({ -2.5f, 0.f, -10.f }, { 0.f, 0.f, 0.f, 0.f }, { 1.f,1.f,1.f });
	sphere = Object3D("../models/sphere/sphere.obj", "../models/sphere", modelShader, sphereTransform, ambiantLight, diffuseLight, specularLight, sphereColor);

	Transform cubeTransform = Transform({ 2.5f, 0.f, -12.f }, { 0.f, 0.f, 0.f, 0.f }, { 1.f,1.f,1.f });
	cube = Object3D("../models/cube/cube.obj", "../models/cube", modelShader, cubeTransform, ambiantLight, diffuseLight, specularLight, cubeColor);

	return true;
}

void Terminate()
{
	glDeleteTextures(1, &TexID);

	modelShader.Destroy();
	lightShader.Destroy();
}

void Render(GLFWwindow* window)
{
	int width, height;
	glfwGetWindowSize(window, &width, &height);

	glViewport(0, 0, width, height);
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	lightCube.render(window);
	sphere.render(window);
	cube.render(window);
}


int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Projet OpenGL", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	Initialise();

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		Render(window);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	Terminate();

	glfwTerminate();
	return 0;
}