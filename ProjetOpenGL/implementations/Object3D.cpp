#include "../headers/Object3D.h"

ModelWithMat::ModelWithMat(const char* model, const char* materialFolder, GLShader shader, Transform tf, LightParams light, float* color, Camera* cam)
{
	this->shader = shader;
	this->position = tf;
	this->color = color;
	this->camera = cam;
	this->light = light;

	loadObjFile(model, materialFolder);
	init();
}

void ModelWithMat::initAttribLocation()
{
	// Call to parent method
	Model::initAttribLocation();


	const size_t stride = sizeof(Vertex);
	auto program = shader.GetProgram();

	int loc_normal = glGetAttribLocation(program, "a_normal");
	glEnableVertexAttribArray(loc_normal);
	glVertexAttribPointer(loc_normal, 3, GL_FLOAT
		, false, stride, (void*)offsetof(Vertex, normal));
}

void ModelWithMat::loadObjFile(const char* filePath, const char* materialFolder)
{
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string err;
	std::string warn;

	bool loaded = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filePath, materialFolder);

	//Si on ne résussit pas a load le modèle, on affiche l'erreur et on quitte
	if (!loaded) {
		std::cerr << err << std::endl;
		exit(1);
	}

	//On récupère les vertexs, normals, et uv
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

	/* Même si on les utilises pas dans cette classe, on les load */
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

	//Pour simplifier, on considère qu'il n'y a qu'un seul material par objet
	//TODO: Possibilité d'ajouter un material par vertex
	this->mat = materialList[0];

	//On load ensuite les faces et on constitue le tableau des vertices
	std::vector<Triangle> triangles;

	for (auto shape = shapes.begin(); shape < shapes.end(); ++shape) {
		const std::vector<tinyobj::index_t>& indices = shape->mesh.indices;
		const std::vector<int>& material_ids = shape->mesh.material_ids;

		for (size_t index = 0; index < material_ids.size(); ++index) {
			// Les données sont enregistrés comme ceci vertex/normal/texture dans un .obj
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

			//TODO: Gestion des indices par la gestion des doublons dans les vertexs
		}

	}
}

void ModelWithMat::updateUniform(GLFWwindow* window)
{
	// Call to parent method
	Model::updateUniform(window);

	auto program = shader.GetProgram();
	glUseProgram(program);

	float* worldPosition = this->position.getWorldMatrix();

	// Calcule de la matrice normale
	GLint normalMatrixLoc = glGetUniformLocation(program, "u_normalMatrix");
	float* inversedWorldMatrix = (float*)malloc(sizeof(float) * 16);
	float* normalMatrix = (float*)malloc(sizeof(float) * 16);
	inverse(worldPosition, inversedWorldMatrix);
	MatrixTranspose(inversedWorldMatrix, normalMatrix);
	glUniformMatrix4fv(normalMatrixLoc, 1, false, normalMatrix);

	// Gestion de la lumière
	GLint ligtPos = glGetUniformLocation(program, "u_lightPos");
	glUniform3fv(ligtPos, 1, this->light.position);
	GLint ambiant = glGetUniformLocation(program, "u_ambiantColor");
	glUniform4fv(ambiant, 1, this->light.ambientColor);
	GLint diffuse = glGetUniformLocation(program, "u_diffuseColor");
	glUniform4fv(diffuse, 1, this->light.diffuseColor);
	GLint specular = glGetUniformLocation(program, "u_specularColor");
	glUniform4fv(specular, 1, this->light.specularColor);

	// Gestion des Materiels
	GLint materialAmbient = glGetUniformLocation(program, "u_material.ambient");
	glUniform3fv(materialAmbient, 1, this->mat.ambient);
	GLint materialDiffuse = glGetUniformLocation(program, "u_material.diffuse");
	glUniform3fv(materialDiffuse, 1, this->mat.diffuse);
	GLint materialSpecular = glGetUniformLocation(program, "u_material.specular");
	glUniform3fv(materialSpecular, 1, this->mat.specular);
	GLint materialShininess = glGetUniformLocation(program, "u_material.shininess");
	glUniform1f(materialShininess, this->mat.shininess);
}

void ModelWithMat::setMaterial(Material mat)
{
	this->mat = mat;
}
