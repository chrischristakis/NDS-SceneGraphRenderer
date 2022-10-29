#include "Object.h"
#include <stdio.h>
#include <nds/arm9/videoGL.h>
#include <nds/arm9/boxtest.h>
#include <stack>

static int counter = 0;  // ID tracking
int Object::poly_counter = 0;

Object::Object(float x, float y, float z) {
	ID = counter++;
	transform.setTranslate(x, y, z);
	parent = nullptr;
}

Object::Object(std::string name, float x, float y, float z) {
	Object(x, y, z);
	this->name = name;
}

Object::~Object() {
	// We're going to destroy children (Ill be put on a list for this comment)
	for (size_t i = 0; i < children.size(); i++)
		delete children[i];
	children.clear();
}

// Used to update the MODELVIEW matrix, relative to the parent's transform
void Object::updateMV() {
	// Load up the MODELVIEW matrix to alter.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// First, apply all parent transforms.
	// We do this by starting with the HIGHEST parent's transform then work our way down, hence the stack.
	// Otherwise, we'd start with our parent's transform, then grandparents, this isn't correct. We start with grandparents then parents.
	std::stack<Object*> parents;
	Object *currPar = parent;
	while (currPar != nullptr) {
		parents.push(currPar);
		currPar = currPar->parent;
	}
	
	// Now that our stack is full, lets work our way down the transforms.
	while (!parents.empty()) {
		currPar = parents.top();
		parents.pop();
		
		printf("\n[%f, %f, %f]", currPar->transform.translate.x, currPar->transform.translate.y, currPar->transform.translate.z);
		glTranslatef(currPar->transform.translate.x, currPar->transform.translate.y, currPar->transform.translate.z);
		glRotatef(currPar->transform.angle, currPar->transform.angleAxis.x, currPar->transform.angleAxis.y, currPar->transform.angleAxis.z);
		currPar = currPar->parent;
	}

	// Now that our global position is that of our parent's time to use our relative transforms.
	glTranslatef(transform.translate.x, transform.translate.y, transform.translate.z);
	glRotatef(transform.angle, transform.angleAxis.x, transform.angleAxis.y, transform.angleAxis.z);

	// We don't scale based off the parent, only input positional and rotational data
	glScalef(transform.scale.x, transform.scale.y, transform.scale.z);

	bounded = mesh->box->bounded();
}

void Object::addChild(Object* object) {
	object->parent = this;
	children.push_back(object);
}

void Object::addMesh(Mesh* mesh) {
	this->mesh = mesh;
}

void Object::updateAndRender() {
	updateMV();
	printf("\n[\"%s\", ID:% d] %s", name.c_str(), ID, bounded ? "rendered" : "unrendered");

	// If the object is off our screen or breaches the maximum amt of polygons, we don't need to render it (Graceful)
	if (bounded && poly_counter + mesh->polys <= MAX_POLYS) {
		poly_counter += mesh->polys;
		render();
	}
}

void Object::renderSelfAndChildren() {
	updateAndRender();
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