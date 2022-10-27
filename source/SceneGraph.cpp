#include "SceneGraph.h"

namespace SceneGraph {
	Object* root;

	void init() {
		root = new Object(0, 0, 0);  // This efines our global origin
	}

	// Adds object to root.
	void addObject(Object* object) {
		root->addChild(object);
	}

	void render() {
		for (size_t i = 0; i < root->children.size(); i++)
			root->children[i]->renderSelfAndChildren();
	}

	void removeObject(Object* object) {
		root->removeChild(object);
	}
}