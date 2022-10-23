#ifndef OBJECT_H
#define OBJECT_H
#include <vector>
#include "Mesh.h"

// Generic object to render, with multiple paramters such as vertices, uv maps, and location.
struct Object {
	float x, y, z;
	std::vector<Mesh> meshes;  // We can use multiple meshes in our object to create a complex mesh.

	Object(float x, float y, float z) : x(x), y(y), z(z) {};

	void addMesh(Mesh mesh);
	void render();
};

#endif