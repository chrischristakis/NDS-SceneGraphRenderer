#ifndef COLOREDOBJECT_H
#define COLOREDOBJECT_H
#include "Object.h"
#include <vector>

struct ColoredObject : public Object {
	std::vector<byte> vertColors;

	ColoredObject(Mesh* mesh, const byte vertColors[], size_t N, float x, float y, float z);
	ColoredObject(std::string name, Mesh* mesh, const byte vertColors[], size_t N, float x, float y, float z);

	void render();
};

#endif