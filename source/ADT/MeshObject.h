#ifndef MESHOBJECT_H
#define MESHOBJECT_H
#include "Object.h"
#include "../Color.h"

class MeshObject : public Object {
	Color3b *color;
public:
	MeshObject(Mesh* mesh, float x, float y, float z);
	~MeshObject();

	void setColor(int r, int g, int b);
	void render();
};

#endif