#include "..\headers\ModelWithTexture.h"


void ModelWithTexture::loadTexture()
{
    //On initialise la texture
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Filtrage bilineaire dans tous les cas (Minification et Magnification)
    // les coordonnees de texture sont limitees a [0 ; 1[
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    int w, h;
    uint8_t* data = stbi_load(fileToLoad, &w, &h, nullptr, STBI_rgb_alpha);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    }
}

void ModelWithTexture::init()
{
	// Cr�ation du VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//On cr�e le VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER
		, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    //On cr�e l'IBO
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices[0], GL_STATIC_DRAW);
	
    loadTexture();
	initAttribLocation();

	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}

void ModelWithTexture::initAttribLocation()
{

    const size_t stride = sizeof(Vertex);
    auto program = shader.GetProgram();

    // Passage des attributs de shader
    int loc_position = glGetAttribLocation(program, "a_position");
    glEnableVertexAttribArray(loc_position);
    glVertexAttribPointer(loc_position, 3, GL_FLOAT
        , false, stride, (void*)offsetof(Vertex, position));

    int loc_uv = glGetAttribLocation(program, "a_texcoords");
    glEnableVertexAttribArray(loc_uv);
    glVertexAttribPointer(loc_uv, 2, GL_FLOAT
        , false, stride, (void*)offsetof(Vertex, uv));

    int loc_normal = glGetAttribLocation(program, "a_normal");
    glEnableVertexAttribArray(loc_normal);
    glVertexAttribPointer(loc_normal, 3, GL_FLOAT
        , false, stride, (void*)offsetof(Vertex, normal));
}

void ModelWithTexture::updateUniform(GLFWwindow* window)
{
    int width, height;
    glfwGetWindowSize(window, &width, &height);

    auto program = shader.GetProgram();
    glUseProgram(program);

    const float fov = 45.0f * M_PI / 180.0f;
    const float f = 1.0f / tanf(fov / 2.0f);
    Matrix4 projectionMatrix = Matrix4::getProjectionMatrix(0.1f, 100.0f, float(width) / float(height), f);

    GLint textureLocation = glGetUniformLocation(program, "u_sampler");
    glUniform1i(textureLocation, 0);

    GLint position = glGetUniformLocation(program, "u_world");
    Matrix4 worldPosition = this->position.getWorldMatrix();
    glUniformMatrix4fv(position, 1, false, worldPosition.getMatrixValue());

    Matrix4 viewMatrix = this->camera->getLookAtMatrix();

    GLint mvp = glGetUniformLocation(program, "u_mvp");
    Matrix4 mvpMatrix = projectionMatrix.getMatrixValue();
    mvpMatrix = mvpMatrix * viewMatrix.getMatrixValue();
    mvpMatrix = mvpMatrix * worldPosition.getMatrixValue();
    glUniformMatrix4fv(mvp, 1, false, mvpMatrix.getMatrixValue());

    // Calcule de la matrice normale
    GLint normalMatrixLoc = glGetUniformLocation(program, "u_normalMatrix");
    Matrix4 normalMatrix = Matrix4(worldPosition.getMatrixValue()).inverse().transpose();
    glUniformMatrix4fv(normalMatrixLoc, 1, false, normalMatrix.getMatrixValue());

    // Gestion de la lumi�re
    GLint ligtPos = glGetUniformLocation(program, "u_lightPos");
    glUniform3fv(ligtPos, 1, this->light.position);
    GLint ambiant = glGetUniformLocation(program, "u_ambiantColor");
    glUniform4fv(ambiant, 1, this->light.ambientColor);
    GLint diffuse = glGetUniformLocation(program, "u_diffuseColor");
    glUniform4fv(diffuse, 1, this->light.diffuseColor);
    GLint specular = glGetUniformLocation(program, "u_specularColor");
    glUniform4fv(specular, 1, this->light.specularColor);
}

ModelWithTexture::ModelWithTexture(const char* model, const char* materialFolder, const char* textureToLoad, GLShader shader, Transform tf, float* color, Camera* cam, LightParams light)
{
    this->shader = shader;
    this->position = tf;
    this->color = color;
    this->camera = cam;
    this->fileToLoad = textureToLoad;
    this->light = light;

    loadObjFile(model, materialFolder);
    init();
}

void ModelWithTexture::render(GLFWwindow* window)
{
    updateUniform(window);

    glBindVertexArray(VAO);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID); //On set la texture
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}
