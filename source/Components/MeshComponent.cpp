#include "MeshComponent.h"
#include <assert.h>

MeshComponent::MeshComponent(const float arr[], size_t N) {
	setVertices(arr, N);
	color = Color3b(255, 255, 255);
}

void MeshComponent::setVertices(const float arr[], size_t N) {
	assert(N % 3 == 0);  // Since we're dealing with x,y,z pairs, we need to abide by this rule.
	vertices.assign(arr, arr + N);
	
	// Since we're only dealing with GL_TRIANGLES, 3 points per vertex (x,y,z), 3 vertices per polygon.
	polys = N / (3 * 3);
}

void MeshComponent::render() {
	glPolyFmt(POLY_ALPHA(31) | POLY_CULL_NONE | POLY_FORMAT_LIGHT0);

	// Now we actually render the vertices.
	glBegin(GL_TRIANGLES);
		glColor3b(color.r, color.g, color.b);
		for (size_t i = 0; i < vertices.size(); i += 3)
			glVertex3f(vertices[i], vertices[i + 1], vertices[i + 2]);
	glEnd();
}