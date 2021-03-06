#include "../headers/Model.h"
#include "../headers/Triangle.h"


Model::Model(const char* model, const char* materialFolder, GLShader shader, Transform tf, float* color, Camera* cam) 
{
	this->shader = shader;
	this->position = tf;
	this->color = color;
	this->camera = cam;

	loadObjFile(model, materialFolder);
	init();
}

/* Load un mod?le obj et les materiels associ?s */
void Model::loadObjFile(const char* filePath, const char* materialFolder)
{
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string err;
	std::string warn;

	bool loaded = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filePath, materialFolder);

	//Si on ne r?sussit pas a load le mod?le, on affiche l'erreur et on quitte
	if (!loaded) {
		std::cerr << err << std::endl;
		exit(1);
	}

	//On r?cup?re les vertexs, normals, et uv
	std::vector<vec3> vertices;
	std::vector<vec3> normals;
	std::vector<vec2> uv;

	for (size_t vec_start = 0; vec_start < attrib.vertices.size(); vec_start += 3) {
		vertices.push_back({
			attrib.vertices[vec_start],
			attrib.vertices[vec_start + 1],
			attrib.vertices[vec_start + 2] });
	}

	for (size_t norm_start = 0; norm_start < attrib.normals.size(); norm_start += 3) {
		normals.push_back({
			attrib.normals[norm_start],
			attrib.normals[norm_start + 1],
			attrib.normals[norm_start + 2] });
	}

	for (size_t uv_start = 0; uv_start < attrib.texcoords.size(); uv_start += 2) {
		uv.push_back({
			attrib.texcoords[uv_start],
			attrib.texcoords[uv_start + 1]
			});
	}

	/* M?me si on les utilises pas dans cette classe, on les load */
	std::vector<Material> materialList;
	for (auto material = materials.begin(); material < materials.end(); ++material) {
		vec3 ambient = vec3(material->ambient[0], material->ambient[1], material->ambient[2]);
		vec3 diffuse = vec3(material->diffuse[0], material->diffuse[1], material->diffuse[2]);
		vec3 specular = vec3(material->specular[0], material->specular[1], material->specular[2]);

		materialList.push_back({
			ambient.toArray(),
			diffuse.toArray(),
			specular.toArray(),
			material->shininess,
			});
	}

	//Pour simplifier, on consid?re qu'il n'y a qu'un seul material par objet
	//TODO: Possibilit? d'ajouter un material par vertex

	//On load ensuite les faces et on constitue le tableau des vertices
	std::vector<Triangle> triangles;

	for (auto shape = shapes.begin(); shape < shapes.end(); ++shape) {
		const std::vector<tinyobj::index_t>& indices = shape->mesh.indices;
		const std::vector<int>& material_ids = shape->mesh.material_ids;

		for (size_t index = 0; index < material_ids.size(); ++index) {
			// Les donn?es sont enregistr?s comme ceci vertex/normal/texture dans un .obj
			triangles.push_back({
				{ indices[3 * index].vertex_index, indices[3 * index + 1].vertex_index, indices[3 * index + 2].vertex_index },
				{ indices[3 * index].normal_index, indices[3 * index + 1].normal_index, indices[3 * index + 2].normal_index },
				{ indices[3 * index].texcoord_index, indices[3 * index + 1].texcoord_index, indices[3 * index + 2].texcoord_index },
				material_ids[index]
				});

		}
	}

	//On convertit les triangles en une liste de vertices et d'indices affichables
	for (auto triangle = triangles.begin(); triangle < triangles.end(); ++triangle) {
		int* vertexIndices = triangle->vertices;
		int* normalIndices = triangle->normals;
		int* uvIndices = triangle->uvs;
		int materialIndice = triangle->material;

		for (int i = 0; i < 3; i++) {
			this->vertices.push_back({
			{vertices[vertexIndices[i]].x, vertices[vertexIndices[i]].y, vertices[vertexIndices[i]].z },
			{normals[normalIndices[i]].x, normals[normalIndices[i]].y, normals[normalIndices[i]].z },
			{uv[uvIndices[i]].x, uv[uvIndices[i]].y}
				});
		}

	}

	ComputeIndices(this->vertices);
}

void Model::init()
{
	// Cr?ation du VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//On cr?e le VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER
		, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	//On cr?e l'IBO
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices[0], GL_STATIC_DRAW);

	initAttribLocation();

	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}

/* Initialise les attributes des shaders */
void Model::initAttribLocation()
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
}

void Model::render(GLFWwindow* window)
{
	updateUniform(window);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

/* Met en place les uniform pour les shaders */
void Model::updateUniform(GLFWwindow* window)
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

	GLint position = glGetUniformLocation(program, "u_world");
	Matrix4 worldPosition = this->position.getWorldMatrix();
	glUniformMatrix4fv(position, 1, false, worldPosition.getMatrixValue());

	GLint view = glGetUniformLocation(program, "u_view");
	Matrix4 viewMatrix = this->camera->getLookAtMatrix();
	glUniformMatrix4fv(view, 1, false, viewMatrix.getMatrixValue());

	GLint mvp = glGetUniformLocation(program, "u_mvp");
	Matrix4 mvpMatrix = projectionMatrix.getMatrixValue();
	mvpMatrix = mvpMatrix * viewMatrix.getMatrixValue();
	mvpMatrix = mvpMatrix * worldPosition.getMatrixValue();
	glUniformMatrix4fv(mvp, 1, false, mvpMatrix.getMatrixValue());

	GLint camPos = glGetUniformLocation(program, "u_cameraPos");
	vec3 pos = this->camera->getPosition();
	glUniform3fv(camPos, 1, pos.toArray());

	// Gestion de la couleur
	GLint colorLoc = glGetUniformLocation(program, "u_color");
	glUniform4fv(colorLoc, 1, this->color);
}

void Model::ComputeIndices(std::vector<Vertex> input)
{
	std::vector<Vertex> vbuffer;
	std::set<Vpair, CmpClass> vertices;
	std::vector<int> indices;
	int index = 0;

	for (int i = 0; i < input.size(); i++)
	{
		std::set<Vpair>::iterator it = vertices.find(std::make_pair(input[i], 0/*this value doesn't matter*/));
		if (it != vertices.end()) indices.push_back(it->second);
		else
		{
			vertices.insert(std::make_pair(input[i], index));
			indices.push_back(index++);
		}
	}

	// Notice that the vertices in the set are not sorted by the index
	// so you'll have to rearrange them like this:
	vbuffer.resize(vertices.size());
	for (std::set<Vpair>::iterator it = vertices.begin(); it != vertices.end(); it++)
		vbuffer[it->second] = it->first;

	this->indices = indices;
	this->vertices = vbuffer;
}
