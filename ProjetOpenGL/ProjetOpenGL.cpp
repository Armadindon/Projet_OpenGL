
// seulement si glew32s.lib
#define GLEW_STATIC 1
#define TINYOBJLOADER_IMPLEMENTATION

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "GL/glew.h"
#include <GLFW/glfw3.h>

#include "../common/ExampleMaterial.h"
#include "../common/GLShader.h"

#include "headers/Matrix4.h"
#include "headers/Vertex.h"
#include "headers/Transform.h"
#include "headers/Object3D.h"
#include "headers/Model.h"
#include "headers/Light.h"
#include "headers/Vector.h"
#include "headers/Camera.h"
#include "headers/ModelWithCubemap.h"
#include "headers/ModelWithTexture.h"


// attention, ce define ne doit etre specifie que dans 1 seul fichier cpp
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

// Pour activer / désactiver la souris
bool showMouse = false;

//Paramètres GUI
float cameraSpeed = 5.f, cameraSensibility = .1f;

int selectedSkybox = 0;
std::string possibleSkyboxes[] = {
	"yokohama",
	"skybox",
	"lycksele"
};


GLShader modelShader, lightShader, skyboxShader, textureShader;

Transform tf;

Model lightCube;
ModelWithMat sphere, cube;
ModelWithTexture fox;
ModelWithCubemap skybox;
Camera* cam;

//Paramètres globaux
float ligtCubeColor[] = { 1.f, 1.f, 1.f, 1.f };
float sphereColor[] = { 0.9882f, 0.7294f, 0.012f, 1.f };
float cubeColor[] = { 1.f, 0.f, 0.f, 1.f };

float lightPose[] = { 0.f, 0.f, -10.f };

// https://www.humus.name/index.php?page=Textures
std::vector<std::string> textureFaces
{
	"../textures/" + possibleSkyboxes[selectedSkybox] + "/right.jpg",
	"../textures/" + possibleSkyboxes[selectedSkybox] + "/left.jpg",
	"../textures/" + possibleSkyboxes[selectedSkybox] + "/top.jpg",
	"../textures/" + possibleSkyboxes[selectedSkybox] + "/bottom.jpg",
	"../textures/" + possibleSkyboxes[selectedSkybox] + "/front.jpg",
	"../textures/" + possibleSkyboxes[selectedSkybox] + "/back.jpg",
};

float ambiant[] = { .2f, .2f, .2f };
float diffuse[] = { .4f, .4f, .4f };
float specular[] = { 1.f, 1.f, 1.f };

LightParams light = {
	lightPose, // Même position que lightPose
	ambiant, // Couleur ambiante -> Peu forte
	diffuse, // Couleur de la lumière -> importante
	specular, // Couleur spéculaire -> Ultra forte
};

/* Fonction appelée lorsque l'utilisateur clique sur son clavier */
/* Le déplacement n'est pas smooth comme ça, donc on le traite dans le update, mais fonctionne bien pour le reste */
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_PRESS) {
		showMouse = !showMouse;
		if (showMouse) glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		else glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {

	if (showMouse) {
		//On forward les infos à imgui
		ImGui::GetIO().MousePos.x = float(xpos);
		ImGui::GetIO().MousePos.y = float(ypos);
	}

	//Si la souris est présente, on ne prend pas en compte le déplacement
	if (!showMouse) cam->mouse_callback(window, xpos, ypos);
}

bool Initialise(GLFWwindow* window)
{
	GLenum ret = glewInit();

	//On initialise ImGUI
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 120");
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	modelShader.LoadVertexShader("shaders/3DModel.vert");
	modelShader.LoadFragmentShader("shaders/3DModel.frag");
	modelShader.Create();

	lightShader.LoadVertexShader("shaders/LightShader.vert");
	lightShader.LoadFragmentShader("shaders/LightShader.frag");
	lightShader.Create();

	skyboxShader.LoadVertexShader("shaders/Skybox.vert");
	skyboxShader.LoadFragmentShader("shaders/Skybox.frag");
	skyboxShader.Create();

	textureShader.LoadVertexShader("shaders/TextureShader.vert");
	textureShader.LoadFragmentShader("shaders/TextureShader.frag");
	textureShader.Create();

	//On active le test de profondeur et le face culling
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_FRAMEBUFFER_SRGB);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	cam = new Camera(
		{ 0.f, 0.f, 0.f }, //position
		{ 0.f, 0.f, -1.f }, //front
		{ 0.0f, 1.0f, 0.0f }, //up
		window,
		cameraSpeed,
		cameraSensibility
	);

	Transform lightCubeTransform = Transform({ lightPose[0], lightPose[1], lightPose[2] }, { 0.f, 0.f, 0.f, 0.f }, { .5f,.5f,.5f });
	lightCube = Model("../models/cube/cube.obj", "../models/cube", lightShader, lightCubeTransform, ligtCubeColor, cam);

	Transform sphereTransform = Transform({ -2.5f, 0.f, -10.f }, { 0.f, 0.f, 0.f, 0.f }, { 1.f,1.f,1.f });
	sphere = ModelWithMat("../models/sphere/sphere.obj", "../models/sphere", modelShader, sphereTransform, light, sphereColor, cam);

	Transform cubeTransform = Transform({ 2.5f, 0.f, -12.f }, { 0.f, 0.f, 0.f, 0.f }, { 1.f,1.f,1.f });
	cube = ModelWithMat("../models/cube/cube.obj", "../models/cube", modelShader, cubeTransform, light, cubeColor, cam);

	Transform foxTransform = Transform({ 7.5f, 0.f, -12.f }, { 0.f, 0.f, 0.f, 0.f }, { .05f,.05f,.05f });
	fox = ModelWithTexture("../models/fox/fox.obj", "../models/fox", "../models/fox/texture.png", textureShader, foxTransform, ligtCubeColor, cam, light);

	skybox = ModelWithCubemap("../models/skybox/skybox.obj", "../models/skybox", textureFaces, skyboxShader, lightCubeTransform, ligtCubeColor, cam);

	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);

	return true;
}

void Terminate()
{
	modelShader.Destroy();
	lightShader.Destroy();
	skyboxShader.Destroy();
	textureShader.Destroy();

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void Render(GLFWwindow* window)
{
	int width, height;
	glfwGetWindowSize(window, &width, &height);

	glViewport(0, 0, width, height);
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//On indique une nouvelle frame à Imgui
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	skybox.render(window);

	lightCube.render(window);
	sphere.render(window);

	//On peut override de cette manière la matériaux chargé
	cube.setMaterial(pearl);
	cube.render(window);

	fox.render(window);
	//On affiche la nouvelle fenetre Imgui
	ImGui::Begin("Fenetre des parametres");
	ImGui::Text("Les parametres ne sont pas accessibles en mode \"Camera\"");
	ImGui::Text("Pour changer de mode ! Appuyez sur ctrl gauche");

	if (ImGui::TreeNode("Parametres Couleurs")) {
		ImGui::ColorEdit4("Couleur du cube de lumière", ligtCubeColor);
		ImGui::ColorEdit4("Couleur du cube", cubeColor);
		ImGui::ColorEdit4("Couleur de la sphere", sphereColor);
		ImGui::TreePop();
	}

	if (ImGui::TreeNode("Parametres Lumiere")) {
		ImGui::ColorEdit3("Couleur de la lumiere ambiante", ambiant);
		ImGui::ColorEdit3("Couleur de la lumiere diffuse", diffuse);
		ImGui::ColorEdit3("Couleur de la lumiere speculaire", specular);
		ImGui::TreePop();
	}

	if (ImGui::TreeNode("Parametres Camera")) {
		if (ImGui::SliderFloat("Camera Speed", &cameraSpeed, 0.0f, 10.0f)) cam->setSpeed(cameraSpeed);
		if(ImGui::SliderFloat("Camera Sensibility", &cameraSensibility, 0.0f, 1.0f)) cam->setSensitivity(cameraSensibility);
		ImGui::TreePop();
	}

	if (ImGui::TreeNode("Parametres Skybox"))
	{
		for (int n = 0; n < 3; n++)
		{
			if (ImGui::Selectable(possibleSkyboxes[n].c_str(), selectedSkybox == n)) {
				selectedSkybox = n;
				skybox.changeTexture({
					"../textures/" + possibleSkyboxes[selectedSkybox] + "/right.jpg",
					"../textures/" + possibleSkyboxes[selectedSkybox] + "/left.jpg",
					"../textures/" + possibleSkyboxes[selectedSkybox] + "/top.jpg",
					"../textures/" + possibleSkyboxes[selectedSkybox] + "/bottom.jpg",
					"../textures/" + possibleSkyboxes[selectedSkybox] + "/front.jpg",
					"../textures/" + possibleSkyboxes[selectedSkybox] + "/back.jpg",
					});
			}

		}
		ImGui::TreePop();
	}

	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Update(GLFWwindow* window) {
	if (!showMouse) cam->processInput(window);
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