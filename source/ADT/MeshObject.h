#ifndef MESHOBJECT_H
#define MESHOBJECT_H
#include "Object.h"
#include "../Color.h"
#include <string>

struct MeshObject : public Object {
	Color3b color;

	MeshObject(Mesh* mesh, float x, float y, float z);
	MeshObject(std::string name, Mesh* mesh, float x, float y, float z);

	void setColor(int r, int g, int b);
	void render();
};

#endif