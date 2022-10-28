#include "Mesh.h"
#include <nds/arm9/videoGL.h>
#include <assert.h>

Mesh::Mesh(float x, float y, float z, float width, float height, float depth,
	const float arr[], size_t N, GL_GLBEGIN_ENUM draw_mode) {
	setVertices(arr, N);
	this->draw_mode = draw_mode;

	box = new Box(x, y, z, width, height, depth);
}

Mesh::~Mesh() {
	delete box;
}

void Mesh::setVertices(const float arr[], size_t N) {
	assert(N % 3 == 0);  // Since we're dealing with x,y,z pairs, we need to abide by this rule.
	vertices.assign(arr, arr + N);
}