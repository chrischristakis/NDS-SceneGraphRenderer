#include "MeshObject.h"
#include <vector>

MeshObject::MeshObject(Mesh* mesh, float x, float y, float z): Object(x,y,z) {
	addMesh(mesh);
	color = new Color3b(255, 255, 255);
}

MeshObject::~MeshObject() {
	delete color;
}

void MeshObject::setColor(int r, int b, int g) {
	color->r = r;
	color->g = g;
	color->b = b;
}

void MeshObject::render() {
	glBegin(mesh->draw_mode);
		glColor3b(color->r, color->g, color->b);
		std::vector<float> &vertices = mesh->vertices;
		for (size_t i = 0; i < vertices.size(); i += 3)
			glVertex3f(vertices[i], vertices[i + 1], vertices[i + 2]);
	glEnd();
}