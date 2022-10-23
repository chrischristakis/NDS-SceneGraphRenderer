#ifndef OBJECT_H
#define OBJECT_H
#include <vector>
#include "Mesh.h"

// Generic object to render, with multiple paramters such as vertices, uv maps, and location.
struct Object {
	float x, y, z;
	Mesh* mesh;

	Object(float x, float y, float z): x(x), y(y), z(z) {}

	void addMesh(Mesh* mesh);
	virtual void render() = 0;
};

#endif