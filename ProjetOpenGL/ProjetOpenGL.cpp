
// seulement si glew32s.lib
#define GLEW_STATIC 1
#define TINYOBJLOADER_IMPLEMENTATION

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

#include "GL/glew.h"

#include <GLFW/glfw3.h>

#include "../common/GLShader.h"
#include "../common/toolsbox.h"

#include "headers/Matrix.h"
#include "headers/Vertex.h"
#include "headers/Transform.h"
#include "headers/Object3D.h"


// attention, ce define ne doit etre specifie que dans 1 seul fichier cpp
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

GLShader modelShader, lightShader;


GLuint TexID;

Transform tf;

Object3D cube, lightCube;
//On les mets en variable globale car giga flemme de les mallocs
float ligtCubeColor[] = { 252.f, 186.f, 3.f, 255.f };
float cubeColor[] = { 252.f, 186.f, 3.f, 255.f };


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

	modelShader.LoadVertexShader("shaders/3DModel.vertex");
	modelShader.LoadFragmentShader("shaders/3DModel.fragment");
	modelShader.Create();

	lightShader.LoadVertexShader("shaders/LightShader.vertex");
	lightShader.LoadFragmentShader("shaders/LightShader.fragment");
	lightShader.Create();

	//On active le test de profondeur et le face culling
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	Transform lightCubeTransform = Transform({ 2.5f, 0.f, -10.f }, { 0.f, 0.f, 0.f, 0.f }, { 1.f,1.f,1.f });
	lightCube = Object3D("../models/cube/cube.obj", "../models/cube", lightShader, lightCubeTransform, ligtCubeColor);

	Transform cubeTransform = Transform({ -2.5f, 0.f, -10.f }, { 0.f, 0.f, 0.f, 0.f }, { 1.f,1.f,1.f });
	cube = Object3D("../models/cube/cube.obj", "../models/cube", modelShader, cubeTransform, cubeColor);

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