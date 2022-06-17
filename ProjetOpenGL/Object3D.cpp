#include "headers/Object3D.h"

void Object3D::clear() {
	vertices.clear();
}

Object3D::Object3D(const char* model, const char* materialFolder, GLShader shader, Transform tf, LightParams light, float* color, Camera* cam)
{
	this->shader = shader;
	this->position = tf;
	this->color = color;
	this->light = light;
	this->camera = cam;
	loadObjFile(model, materialFolder);
	init();
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

void Object3D::init()
{
	const size_t stride = sizeof(Vertex);
	auto program = shader.GetProgram();

	// TODO : Gestion des textures et des materiaux

	// Création du VAO
	// TODO: N'utiliser un seul VAO pour tous les objets de la scène (changement de VAO couteux)
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//On crée le VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER
		, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	//TODO: Recreer l'IBO

	// Passage des attributs de shader
	int loc_position = glGetAttribLocation(program, "a_position");
	glEnableVertexAttribArray(loc_position);
	glVertexAttribPointer(loc_position, 3, GL_FLOAT
		, false, stride, (void*)offsetof(Vertex, position));

	int loc_normal = glGetAttribLocation(program, "a_normal");
	glEnableVertexAttribArray(loc_normal);
	glVertexAttribPointer(loc_normal, 3, GL_FLOAT
		, false, stride, (void*)offsetof(Vertex, normal));

	int loc_uv = glGetAttribLocation(program, "a_texcoords");
	glEnableVertexAttribArray(loc_uv);
	glVertexAttribPointer(loc_uv, 2, GL_FLOAT
		, false, stride, (void*)offsetof(Vertex, uv));

	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}

void Object3D::render(GLFWwindow* window)
{
	int width, height;
	glfwGetWindowSize(window, &width, &height);

	auto program = shader.GetProgram();
	glUseProgram(program);

	const float fov = 45.0f * M_PI / 180.0f;
	const float f = 1.0f / tanf(fov / 2.0f);
	const float* projectionMatrix = getProjectionMatrix(0.1f, 100.0f, float(width) / float(height), f);

	//TODO: Faire la matrice MVP ici (pour éviter les calculs dans le shader)
	GLint proj = glGetUniformLocation(program, "u_projection");
	glUniformMatrix4fv(proj, 1, false, projectionMatrix);

	GLint position = glGetUniformLocation(program, "u_world");
	float* worldPosition = this->position.getWorldMatrix();
	glUniformMatrix4fv(position, 1, false, worldPosition);

	GLint view = glGetUniformLocation(program, "u_view");
	float* viewMatrix = this->camera->getLookAtMatrix();
	glUniformMatrix4fv(view, 1, false, viewMatrix);

	GLint camPos = glGetUniformLocation(program, "u_cameraPos");
	vec3 pos = this->camera->getPosition();
	glUniform3fv(camPos, 1, pos.toArray());

	// Calcule de la matrice normale
	GLint normalMatrixLoc = glGetUniformLocation(program, "u_normalMatrix");
	float* inversedWorldMatrix = (float*)malloc(sizeof(float) * 16);
	float* normalMatrix = (float*)malloc(sizeof(float) * 16);
	inverse(worldPosition, inversedWorldMatrix);
	MatrixTranspose(inversedWorldMatrix, normalMatrix);
	glUniformMatrix4fv(normalMatrixLoc, 1, false, normalMatrix);

	// Gestion de la couleur
	GLint colorLoc = glGetUniformLocation(program, "u_color");
	glUniform4fv(colorLoc, 1, this->color);

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

	glBindVertexArray(VAO);

	// Quand l'IBO sera recrée, utiliser glDrawElements (optimisation)
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());

	glBindVertexArray(0);
}

void Object3D::setMaterial(Material mat)
{
	this->mat = mat;
}
