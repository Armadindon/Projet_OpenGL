#include "..\headers\ModelWithCubemap.h"


void ModelWithCubemap::loadCubeMapTexture()
{
    //On crée la texture
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < this->textureFaces.size(); i++)
    {
        unsigned char* data = stbi_load(this->textureFaces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            //On incrémente pour chaque 
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0, GL_SRGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
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
	// Création du VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//On crée le VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER
		, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
	
    //On crée l'IBO
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices[0], GL_STATIC_DRAW);

    loadCubeMapTexture();
	initAttribLocation();


	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}

void ModelWithCubemap::initAttribLocation()
{
    const size_t stride = sizeof(Vertex);
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
    Matrix4 projectionMatrix = Matrix4::getProjectionMatrix(0.1f, 100.0f, float(width) / float(height), f);

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
    glDepthMask(GL_FALSE);  // Afin de permettre d'afficher la skybox derrière chaque objet
    updateUniform(window);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID); //On set la texture

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    glDepthMask(GL_TRUE);
    glBindVertexArray(0);
}

void ModelWithCubemap::changeTexture(std::vector<std::string> textureFaces)
{
    this->textureFaces = textureFaces;
    loadCubeMapTexture();
}
