#include "MeshComponent.h"
#include <assert.h>

Mesh::Mesh(const float arr[], size_t N) {
	setVertices(arr, N);
	color = Color3b(255, 255, 255);
}

void Mesh::setVertices(const float arr[], size_t N) {
	assert(N % 3 == 0);  // Since we're dealing with x,y,z pairs, we need to abide by this rule.
	vertices.assign(arr, arr + N);

	// Since we're only dealing with GL_TRIANGLES, 3 points per vertex (x,y,z), 3 vertices per polygon.
	polys = N / (3 * 3);
}

MeshComponent::MeshComponent(const float arr[], size_t N) {
	Mesh* m = new Mesh(arr, N);
	meshes.insert({ 0, m });  // First mesh (no LOD) is drawn when closest to the camera.
}

MeshComponent::~MeshComponent() {
	for (auto it = meshes.begin(); it != meshes.end(); it++)
		delete it->second;
	meshes.clear();
}

void MeshComponent::addLODMesh(float distance, const float arr[], size_t N) {
	meshes.insert({ distance, new Mesh(arr, N) });
}