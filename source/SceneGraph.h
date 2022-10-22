#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H
#include <stdio.h>

namespace SceneGraph {
	void init();

	void render();
	void update();

	void addObject(/*object*/);
	void removeObject(/*object*/);
	void transformObject(/*transform*/);
}

#endif