#include "Object3D.h"


void Object3D::clear() {
    vertices.clear();
    triangles.clear();
}

void Object3D::init()
{

    //On crée le VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER
        , sizeof(vertices), &vertices, GL_STATIC_DRAW);

    //On crée l'IBO
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(triangles), &triangles, GL_STATIC_DRAW);


    const size_t stride = sizeof(Vertex);
    auto program = shader.GetProgram();

    // Créatuib du VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    // Passage des attributs de shader
    int loc_position = glGetAttribLocation(program, "a_position");
    glEnableVertexAttribArray(loc_position);
    glVertexAttribPointer(loc_position, 3, GL_FLOAT
        , false, stride, (void*)offsetof(Vertex, position));

    int loc_uv = glGetAttribLocation(program, "a_texcoords");
    glEnableVertexAttribArray(loc_uv);
    glVertexAttribPointer(loc_uv, 2, GL_FLOAT
        , false, stride, (void*)offsetof(Vertex, uv));
}

void Object3D::loadObjFile(const char* filePath, const char* materialFolder)
{
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string err;
    std::string warn;

    //On clear au cas ou
    clear();

    bool loaded = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filePath, materialFolder);

    //Si on ne résussit pas a load le modèle, on affiche l'erreur et on quitte
    if (!loaded) {
        std::cerr << err << std::endl;
        exit(1);
    }

    //On commence à récupérer les vertexs et leurs normales
    for (int i = 0; i < attrib.vertices.size(); i+= 3) {
        vertices.push_back({ 
            {attrib.vertices[i], attrib.vertices[i + 1], attrib.vertices[i + 2]}, 
            {attrib.normals[i], attrib.normals[i + 1], attrib.normals[i + 2]},
            {0.f, 0.f} 
        });
    }

    //On load ensuite les UVS
    for (int i = 0; i < attrib.texcoords.size(); i += 2) {
        vertices[i / 2].uv[0] = attrib.texcoords[i];
        vertices[i / 2].uv[1] = attrib.texcoords[i + 1];
    }

    //On load ensuite les faces
    for (auto shape = shapes.begin(); shape < shapes.end(); ++shape) {
        const std::vector<tinyobj::index_t>& indices = shape->mesh.indices;
        const std::vector<int>& material_ids = shape->mesh.material_ids;

        for (size_t index = 0; index < material_ids.size(); ++index) {
            // offset by 3 because values are grouped as vertex/normal/texture
            triangles.push_back({
                { indices[3 * index].vertex_index, indices[3 * index + 1].vertex_index, indices[3 * index + 2].vertex_index },
                { indices[3 * index].normal_index, indices[3 * index + 1].normal_index, indices[3 * index + 2].normal_index },
                { indices[3 * index].texcoord_index, indices[3 * index + 1].texcoord_index, indices[3 * index + 2].texcoord_index },
                material_ids[index]
                });
        }
    }

    //TODO : Ajouter les materials aux objets, et les loads ici
}

void Object3D::render(GLFWwindow* window)
{
    int width, height;
    glfwGetWindowSize(window, &width, &height);

    auto program = shader.GetProgram();
    glUseProgram(program);

    GLint textureLocation = glGetUniformLocation(program, "u_sampler");
    glUniform1i(textureLocation, 0);

    const float zNear = 0.1f;
    const float zFar = 100.0f;
    const float aspect = float(width) / float(height);
    const float fov = 45.0f * M_PI / 180.0f;
    const float f = 1.0f / tanf(fov / 2.0f);
    const float projection[] = {
        f / aspect, 0.f, 0.f, 0.f,
        0.f, f, 0.f, 0.f,
        0.f, 0.f, ((zFar + zNear) / (zNear - zFar)), -1.f,
        0.f, 0.f, ((2 * zNear * zFar) / (zNear - zFar)), 0.f
    };

    GLint proj = glGetUniformLocation(program, "u_projection");
    glUniformMatrix4fv(proj, 1, false, projection);

    GLint position = glGetUniformLocation(program, "u_position");
    float* worldPosition = this->position.getWorldMatrix();
    glUniformMatrix4fv(position, 1, false, worldPosition);

    glBindVertexArray(VAO);

    glDrawElements(GL_TRIANGLES, vertices.size(), GL_UNSIGNED_SHORT, 0);
}
