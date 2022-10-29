#include "ColoredObject.h"
#include <assert.h>

// Vert colors should map 1:1 with each defined vertex, and N is the size of said array.
ColoredObject::ColoredObject(Mesh* mesh, const byte vertColors[], size_t N, float x, float y, float z)
	: Object(x, y, z) {
	assert(N == mesh->vertices.size()); // 3 points per vert, 3 colors per vert, so must be same size
	this->vertColors.assign(vertColors, vertColors + N);
	addMesh(mesh);
}

// Vert colors should map 1:1 with each defined vertex, and N is the size of said array.
ColoredObject::ColoredObject(std::string name, Mesh* mesh, const byte vertColors[], size_t N,
	float x, float y, float z) : ColoredObject(mesh, vertColors, N, x, y, z) {
	this->name = name;
}

void ColoredObject::render() {
	glPolyFmt(POLY_ALPHA(31) | POLY_CULL_NONE | POLY_FORMAT_LIGHT0);

	// Now we actually render the vertices.
	glBegin(mesh->draw_mode);
	std::vector<float> &vertices = mesh->vertices;
	for (size_t i = 0; i < vertices.size(); i += 3) {
		glColor3b(vertColors[i], vertColors[i + 1], vertColors[i + 2]);
		glVertex3f(vertices[i], vertices[i + 1], vertices[i + 2]);
	}
	glEnd();
}