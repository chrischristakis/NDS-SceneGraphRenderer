#include "Mesh.h"
#include <nds/arm9/videoGL.h>

Mesh::Mesh(const float arr[], size_t N, GL_GLBEGIN_ENUM draw_mode) {
	setVertices(arr, N);
	this->draw_mode = draw_mode;
}

void Mesh::setVertices(const float arr[], size_t N) {
	vertices.assign(arr, arr + N);
}