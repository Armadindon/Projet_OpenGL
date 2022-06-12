#include "Object3D.h"


void Object3D::clear() {
	vertices.clear();
}

Object3D::Object3D(const char* model, const char* materialFolder, GLShader shader, Transform tf)
{
	this->shader = shader;
	this->position = tf;
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

	//Si on ne r�sussit pas a load le mod�le, on affiche l'erreur et on quitte
	if (!loaded) {
		std::cerr << err << std::endl;
		exit(1);
	}

	//On r�cup�re les vertexs, normals, et uv
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
		materialList.push_back({
			*material->ambient,
			*material->diffuse,
			*material->specular,
			material->shininess,
			});
	}

	//On load ensuite les faces et on constitue le tableau des vertices
	std::vector<Triangle> triangles;

	for (auto shape = shapes.begin(); shape < shapes.end(); ++shape) {
		const std::vector<tinyobj::index_t>& indices = shape->mesh.indices;
		const std::vector<int>& material_ids = shape->mesh.material_ids;

		for (size_t index = 0; index < material_ids.size(); ++index) {
			// Les donn�es sont enregistr�s comme ceci vertex/normal/texture dans un .obj
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
			{uv[uvIndices[i]].x, uv[uvIndices[i]].y},
			materialList[materialIndice]
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

	// Cr�ation du VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//On cr�e le VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER
		, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	//TODO: Recreer l'IBO

	// Passage des attributs de shader
	// TODO: G�rer les normales
	int loc_position = glGetAttribLocation(program, "a_position");
	glEnableVertexAttribArray(loc_position);
	glVertexAttribPointer(loc_position, 3, GL_FLOAT
		, false, stride, (void*)offsetof(Vertex, position));

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

	// Quand l'IBO sera recr�e, utiliser glDrawElements (optimisation)
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());

	glBindVertexArray(0);
}