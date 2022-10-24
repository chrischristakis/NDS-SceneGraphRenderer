#ifndef OBJECT_H
#define OBJECT_H
#include <vector>
#include "Mesh.h"
#include "Transform.h"

// Generic object to render, with multiple paramters such as vertices, uv maps, and location.
struct Object {
	Transform transform;
	Mesh* mesh;
	Object* parent;

	Object(float x, float y, float z);

	void updateMV();
	void addMesh(Mesh* mesh);
	virtual void render() = 0;
};

#endif