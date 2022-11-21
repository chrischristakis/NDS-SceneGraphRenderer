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

void Object::addChild(Object* object) {
	object->parent = this;
	children.push_back(object);
}

void Object::addMesh(Mesh* mesh) {
	this->mesh = mesh;
}

void Object::updateAndRender() {
	// Load up the MODELVIEW matrix to alter.
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	// Apply the current transforms that will be applied to children (Scale doesnt apply to children)
	glTranslatef(transform.translate.x, transform.translate.y, transform.translate.z);
	glRotatef(transform.angle, transform.angleAxis.x, transform.angleAxis.y, transform.angleAxis.z);

	// Loop through children and render them, building on the parent transforms.
	for (size_t i = 0; i < children.size(); i++)
		children[i]->updateAndRender();

	// We don't want to scale our children, that's why this is down here.
	glScalef(transform.scale.x, transform.scale.y, transform.scale.z);

	//Some bounding box testing to clip  polygons offscreen.
	bounded = mesh->box->bounded();
	printf("\n[\"%s\", ID:% d] %s", name.c_str(), ID, bounded ? "rendered" : "unrendered");
	if (bounded && poly_counter + mesh->polys <= MAX_POLYS) {  // Only draw if bounded, and we have polygons to spare.
		poly_counter += mesh->polys;
		render();
	}

	glPopMatrix(1); // Once we've rendered our object, we can dispose of our current matrix and move uo the hiearchy
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