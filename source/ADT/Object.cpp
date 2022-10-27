#include "Object.h"
#include <stdio.h>

static int counter = 0;  // ID tracking

Object::Object(float x, float y, float z) {
	ID = counter++;
	transform.setTranslate(x, y, z);
	parent = nullptr;
}

Object::~Object() {
	// We're going to destroy children (Ill be put on a list for this comment)
	for (size_t i = 0; i < children.size(); i++)
		delete children[i];
	children.clear();
}

// Used to update the MODELVIEW matrix, relative to the parent's transform
void Object::updateMV() {
	Transform parentTransform;  // Use identity transform if no parent exists (no effect)
	
	if (parent != nullptr)
		parentTransform = parent->transform;  // If we have a parent, use it's transform as our global position!

	// Load up the MODELVIEW matrix to alter.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// First, apply parent transform.
	glTranslatef(parentTransform.translate.x, parentTransform.translate.y, parentTransform.translate.z);
	glRotatef(parentTransform.angle, parentTransform.angleAxis.x, parentTransform.angleAxis.y, parentTransform.angleAxis.z);

	// Now that our global position is that of our parent's time to use our relative transforms.
	glTranslatef(transform.translate.x, transform.translate.y, transform.translate.z);
	glRotatef(transform.angle, transform.angleAxis.x, transform.angleAxis.y, transform.angleAxis.z);

	// We don't scale based off the parent, only input positional and rotational data
	glScalef(transform.scale.x, transform.scale.y, transform.scale.z);
}

void Object::addChild(Object* object) {
	object->parent = this;
	children.push_back(object);
}

void Object::addMesh(Mesh* mesh) {
	this->mesh = mesh;
}

void Object::renderSelfAndChildren() {
	printf("\nID: %d", ID);
	render();
	for (size_t i = 0; i < children.size(); i++)
		children[i]->renderSelfAndChildren();
}

// DFS through children to remove an object.
void Object::removeChild(Object* object) {
	size_t index = 0;
	while (index < children.size()) {
		if (object == children[index]) {
			children.erase(children.begin() + index);
			delete object;
			return;
		}
		children[index]->removeChild(object);
		index++;
	}
}