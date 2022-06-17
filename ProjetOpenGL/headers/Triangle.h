#pragma once

#ifndef _Triangle_H_
#define _Triangle_H_

struct Triangle {
	//Index des vertices
	int vertices[3];
	//Index des normales
	int normals[3];
	//Index des uvs
	int uvs[3];
	//Index du material
	int material;
};

#endif