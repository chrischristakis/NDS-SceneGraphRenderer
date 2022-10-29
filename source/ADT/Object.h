#ifndef OBJECT_H
#define OBJECT_H
#include <vector>
#include <string>
#include "Mesh.h"
#include "Transform.h"

// Generic object to render, with multiple paramters such as vertices, uv maps, and location.
struct Object {
	Transform transform;
	Mesh* mesh;
	Object* parent;
	std::vector<Object*> children;
	int ID;
	int bounded;  // Used for simple bounded clipping using BoxTest 
	std::string name;

	static const int MAX_POLYS = 4000;
	static int poly_counter;

	Object(float x, float y, float z);
	Object(std::string name, float x, float y, float z);
	virtual ~Object();

	void updateMV();
	void addChild(Object* object);
	void removeChild(Object* object);
	void addMesh(Mesh* mesh);
	virtual void render() {};
	void updateAndRender();
	void renderSelfAndChildren();
};

#endif