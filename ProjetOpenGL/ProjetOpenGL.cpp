
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
#include "headers/Model.h"
#include "headers/Light.h"
#include "headers/Vector.h"
#include "headers/Camera.h"
#include "headers/ModelWithCubemap.h"
#include "../common/ExampleMaterial.h"


// attention, ce define ne doit etre specifie que dans 1 seul fichier cpp
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

GLShader modelShader, lightShader, skyboxShader;

GLuint TexID;

Transform tf;

Model lightCube;
ModelWithMat sphere, cube;
ModelWithCubemap skybox;
Camera *cam;

//Paramètres globaux
float ligtCubeColor[] = { 1.f, 1.f, 1.f, 1.f };
float sphereColor[] = { 0.9882f, 0.7294f, 0.012f, 1.f };
float cubeColor[] = { 1.f, 0.f, 0.f, 1.f };

float lightPose[] = { 0.f, 0.f, -10.f };

// https://www.humus.name/index.php?page=Textures
std::vector<std::string> textureFaces
{
	"../textures/yokohama/right.jpg",
	"../textures/yokohama/left.jpg",
	"../textures/yokohama/top.jpg",
	"../textures/yokohama/bottom.jpg",
	"../textures/yokohama/front.jpg",
	"../textures/yokohama/back.jpg",
};

LightParams light = {
	{ lightPose[0], lightPose[1], lightPose[2] }, // Même posiotion que lightPose
	{.4f, .4f, .4f}, // Couleur ambiante -> Peu forte
	{.8f, .8f, .8f}, // Couleur de la lumière -> importante
	{1.f, 1.f, 1.f}, // Couleur spéculaire -> Ultra forte
};

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

/* Fonction appelée lorsque l'utilisateur clique sur son clavier */
/* Le déplacement n'est pas smooth comme ça */
/*
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	cam.processInput(key);
}
*/

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	cam->mouse_callback(window, xpos, ypos);
}

bool Initialise(GLFWwindow* window)
{
	GLenum ret = glewInit();

	modelShader.LoadVertexShader("shaders/3DModel.vert");
	modelShader.LoadFragmentShader("shaders/3DModel.frag");
	modelShader.Create();

	lightShader.LoadVertexShader("shaders/LightShader.vert");
	lightShader.LoadFragmentShader("shaders/LightShader.frag");
	lightShader.Create();

	skyboxShader.LoadVertexShader("shaders/Skybox.vert");
	skyboxShader.LoadFragmentShader("shaders/Skybox.frag");
	skyboxShader.Create();

	//On active le test de profondeur et le face culling
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	cam = new Camera(
		{ 0.f, 0.f, 0.f }, //position
		{ 0.f, 0.f, -1.f }, //front
		{ 0.0f, 1.0f, 0.0f }, //up
		window
	);

	Transform lightCubeTransform = Transform({ lightPose[0], lightPose[1], lightPose[2] }, { 0.f, 0.f, 0.f, 0.f }, { .5f,.5f,.5f });
	lightCube = Model("../models/cube/cube.obj", "../models/cube", lightShader, lightCubeTransform, ligtCubeColor, cam);

	Transform sphereTransform = Transform({ -2.5f, 0.f, -10.f }, { 0.f, 0.f, 0.f, 0.f }, { 1.f,1.f,1.f });
	sphere = ModelWithMat("../models/sphere/sphere.obj", "../models/sphere", modelShader, sphereTransform, light, sphereColor, cam);

	Transform cubeTransform = Transform({ 2.5f, 0.f, -12.f }, { 0.f, 0.f, 0.f, 0.f }, { 1.f,1.f,1.f });
	cube = ModelWithMat("../models/cube/cube.obj", "../models/cube", modelShader, cubeTransform, light, cubeColor, cam);

	skybox = ModelWithCubemap("../models/skybox/skybox.obj", "../models/skybox", textureFaces, skyboxShader, lightCubeTransform, ligtCubeColor, cam);

	//glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);

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

	skybox.render(window);

	lightCube.render(window);
	sphere.render(window);

	//On peut override de cette manière la matériaux chargé
	cube.setMaterial(pearl);
	cube.render(window);
}

void Update(GLFWwindow* window) {
	cam->processInput(window);
}


int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1280, 720, "Projet OpenGL", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	Initialise(window);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Update Here */
		Update(window);

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