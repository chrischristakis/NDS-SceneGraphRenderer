#include "MeshObject.h"
#include <vector>
#include <stdio.h>

MeshObject::MeshObject(Mesh* mesh, float x, float y, float z): Object(x,y,z) {
	addMesh(mesh);
	color = Color3b(255, 255, 255);  // Default to white
}

MeshObject::MeshObject(std::string name, Mesh* mesh, float x, float y, float z): MeshObject(mesh,x,y,z) {
	this->name = name;
}

void MeshObject::setColor(int r, int g, int b) {
	color = Color3b(r, g, b);
}

void MeshObject::render() {
	glPolyFmt(POLY_ALPHA(31) | POLY_CULL_NONE | POLY_FORMAT_LIGHT0);

	// Now we actually render the vertices.
	glBegin(mesh->draw_mode);
	glColor3b(color.r, color.g, color.b);
	std::vector<float> &vertices = mesh->vertices;
	for (size_t i = 0; i < vertices.size(); i += 3)
		glVertex3f(vertices[i], vertices[i + 1], vertices[i + 2]);
	glEnd();
}