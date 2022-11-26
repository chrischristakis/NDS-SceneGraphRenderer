#ifndef MESHCOMPONENT_H
#define MESHCOMPONENT_H
#include <vector>
#include <nds/arm9/videoGL.h>
#include "Component.h"
#include "../Color.h"

struct MeshComponent : public Component {

	std::vector<float> vertices;
	int polys;  // How many polygons our mesh has.
	Color3b color;  // Our mesh's color should we have no texture.

	// Provide just an array of vertives and their size.
	MeshComponent(const float arr[], size_t N);

	//! Vertices must be in the form of [x, y, z, x, y, z, ... ]
	void setVertices(const float arr[], size_t N);
	void render();
};

#endif