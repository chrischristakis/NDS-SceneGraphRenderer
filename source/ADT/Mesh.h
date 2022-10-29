#ifndef MESH_H
#define MESH_H
#include <vector>
#include <nds/arm9/videoGL.h>
#include "Box.h"
#include "../Constants.h"

// A mesh simply stores vertices and how to draw them.
struct Mesh {
	std::vector<float> vertices;
	Box* box;
	GL_GLBEGIN_ENUM draw_mode;

	int polys;

	Mesh(float x, float y, float z, float width, float height, float depth,
		const float arr[], size_t N, DrawMode draw_mode);

	~Mesh();

	//! Vertices should be in the form of [x, y, z, x, y, z, ... ]
	void setVertices(const float arr[], size_t N);
};

#endif