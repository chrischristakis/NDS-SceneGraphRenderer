#include "Object.h"

Object::Object(float x, float y, float z) {
	transform.setTranslate(x, y, z);
	parent = nullptr;
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

void Object::addMesh(Mesh* mesh) {
	this->mesh = mesh;
}