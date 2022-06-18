#include "..\headers\ModelWithCubemap.h"

//Pour des tests
float skyboxVertices[] = {
    // positions          
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f
};


void ModelWithCubemap::loadCubeMapTexture()
{
    //On cr�e la texture
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < this->textureFaces.size(); i++)
    {
        unsigned char* data = stbi_load(this->textureFaces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            //On incr�mente pour chaque 
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
            );
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap texture failed to load at path: " << this->textureFaces[i] << std::endl;
            stbi_image_free(data);
        }
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void ModelWithCubemap::init()
{
	// Cr�ation du VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//On cr�e le VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER
		, vertices.size() * sizeof(Vertex), &skyboxVertices, GL_STATIC_DRAW);
	
    loadCubeMapTexture();

	//TODO: Recreer l'IBO
	initAttribLocation();


	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}

void ModelWithCubemap::initAttribLocation()
{
    const size_t stride = sizeof(float) * 3;
    auto program = shader.GetProgram();

    // Passage des attributs de shader
    int loc_position = glGetAttribLocation(program, "a_position");
    glEnableVertexAttribArray(loc_position);
    glVertexAttribPointer(loc_position, 3, GL_FLOAT
        , false, stride, (void*)offsetof(Vertex, position));
}

void ModelWithCubemap::updateUniform(GLFWwindow* window)
{
    int width, height;
    glfwGetWindowSize(window, &width, &height);

    auto program = shader.GetProgram();
    glUseProgram(program);

    const float fov = 45.0f * M_PI / 180.0f;
    const float f = 1.0f / tanf(fov / 2.0f);
    Matrix4 projectionMatrix = getProjectionMatrix(0.1f, 100.0f, float(width) / float(height), f);

    //TODO: Faire la matrice MVP ici (pour �viter les calculs dans le shader)
    GLint proj = glGetUniformLocation(program, "u_projection");
    glUniformMatrix4fv(proj, 1, false, projectionMatrix.getMatrixValue());

    GLint view = glGetUniformLocation(program, "u_view");
    Matrix4 viewMatrix = this->camera->getLookAtMatrix();
    glUniformMatrix4fv(view, 1, false, viewMatrix.getMatrixValue());

    GLint tex = glGetUniformLocation(program, "u_skybox");
    glUniform1i(tex, 0);
}

ModelWithCubemap::ModelWithCubemap(const char* model, const char* materialFolder, std::vector<std::string> cubemap, GLShader shader, Transform tf, float* color, Camera* cam)
{
    this->shader = shader;
    this->position = tf;
    this->color = color;
    this->camera = cam;
    this->textureFaces = cubemap;

    loadObjFile(model, materialFolder);
    init();
}

void ModelWithCubemap::render(GLFWwindow* window)
{
    glDepthMask(GL_FALSE);  // Afin de permettre d'afficher la skybox derri�re chaque objet
    updateUniform(window);

    glBindVertexArray(VAO);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID); //On set la texture

    // Quand l'IBO sera recr�e, utiliser glDrawElements (optimisation)
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glDepthMask(GL_TRUE);
    glBindVertexArray(0);
}
