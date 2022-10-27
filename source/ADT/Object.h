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
	std::vector<Object*> children;
	int ID;

	Object(float x, float y, float z);
	virtual ~Object();

	void updateMV();
	void addChild(Object* object);
	void removeChild(Object* object);
	void addMesh(Mesh* mesh);
	virtual void render() {};
	void renderSelfAndChildren();
};

#endif