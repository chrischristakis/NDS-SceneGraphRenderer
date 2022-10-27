#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H
#include <stdio.h>
#include "ADT/Object.h"

namespace SceneGraph {
	extern Object* root;

	void init();

	void render();

	void addObject(Object* object);
	void removeObject(Object* object);
	void transformObject(/*transform*/);
}

#endif