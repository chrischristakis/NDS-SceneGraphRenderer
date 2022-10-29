#include "Mesh.h"
#include <nds/arm9/videoGL.h>
#include <assert.h>

Mesh::Mesh(float x, float y, float z, float width, float height, float depth,
	const float arr[], size_t N, DrawMode draw_mode) {
	setVertices(arr, N);

	switch (draw_mode) {
		case DrawMode::TRIANGLES:
			this->draw_mode = GL_TRIANGLES;
			polys = N / (3 * 3);  // 3 points per vert, 3 verts per polygon.
			break;
		case DrawMode::QUAD:
			this->draw_mode = GL_QUAD;
			polys = N / (3 * 4);  // 3 points per vert, 4 verts per polygon.
			break;
	}

	box = new Box(x, y, z, width, height, depth);
}

Mesh::~Mesh() {
	delete box;
}

void Mesh::setVertices(const float arr[], size_t N) {
	assert(N % 3 == 0);  // Since we're dealing with x,y,z pairs, we need to abide by this rule.
	vertices.assign(arr, arr + N);
}