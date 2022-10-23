#ifndef MESH_H
#define MESH_H
#include <vector>
#include <nds/arm9/videoGL.h>

// A mesh simply stores vertices and how to draw them.
struct Mesh {
	std::vector<float> vertices;
	GL_GLBEGIN_ENUM draw_mode;

	Mesh(const float arr[], size_t N, GL_GLBEGIN_ENUM draw_mode);

	//! Vertices should be in the form of [x, y, z, x, y, z, ... ]
	void setVertices(const float arr[], size_t N);
};

#endif