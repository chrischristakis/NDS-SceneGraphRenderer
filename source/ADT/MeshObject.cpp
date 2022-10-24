#include "MeshObject.h"
#include <vector>
#include "Transform.h"
#include <stdio.h>

MeshObject::MeshObject(Mesh* mesh, float x, float y, float z): Object(x,y,z) {
	addMesh(mesh);
	color = Color3b(255, 255, 255);  // Default to white
}

void MeshObject::setColor(int r, int g, int b) {
	color = Color3b(r, g, b);
}

void MeshObject::render() {
	updateMV();  // Set our MODELVIEW matrix

	// Now we actually render the vertices.
	glBegin(mesh->draw_mode);
		glColor3b(color.r, color.g, color.b);
		std::vector<float> &vertices = mesh->vertices;
		for (size_t i = 0; i < vertices.size(); i += 3)
			glVertex3f(vertices[i], vertices[i + 1], vertices[i + 2]);
	glEnd();
}