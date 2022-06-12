#pragma once

struct Triangle {
	//Index des vertices
	int vertices[3];
	//Index des normales
	int normals[3];
	//Index des uvs
	int uvs[3];
	//Index du material (TODO)
	int material;
};