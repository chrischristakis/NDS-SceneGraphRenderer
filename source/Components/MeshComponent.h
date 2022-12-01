#ifndef MESHCOMPONENT_H
#define MESHCOMPONENT_H
#include <vector>
#include <map>
#include <nds/arm9/videoGL.h>
#include "Component.h"
#include "../Color.h"

struct Mesh {
	std::vector<float> vertices;
	int polys;  // How many polygons our mesh has.
	Color3b color;  // Our mesh's color should we have no texture.

	Mesh(const float arr[], size_t N);

	//! Vertices must be in the form of [x, y, z, x, y, z, ... ]
	void setVertices(const float arr[], size_t N);
};

struct MeshComponent : public Component {

	//Tracks the distance a mesh will be drawn at.
	std::map<float, Mesh*> meshes;

	~MeshComponent();

	// Provide just an array of vertives and their size.
	MeshComponent(const float arr[], size_t N);

	// Make a new mesh that will be rendered at a specified distance
	void addLODMesh(float distance, const float arr[], size_t N);
};

#endif