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