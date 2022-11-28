#include "GameObject.h"
#include "../Components/MeshComponent.h"
#include "../Components/BoxComponent.h"
#include "../Components/AnimationComponent.h"
#include "../Constants.h"
#include "../Components/RenderingSystem.h"
#include <nds/arm9/videoGL.h>

int id_counter = 0;
int GameObject::poly_counter = 0;

GameObject::GameObject(float x, float y, float z) {
	ID = id_counter++;  // Set then increment our unique counter.
	transform.setTranslate(x, y, z);
	parent = nullptr;
}

GameObject::GameObject(std::string name, float x, float y, float z): GameObject(x,y,z) {
	this->name = name;
}

GameObject::~GameObject() {
	// More child decimation. Brutal.
	for (size_t i = 0; i < children.size(); i++)
		delete children[i];
	children.clear();
}

void GameObject::addChild(GameObject* obj) {
	obj->parent = this;
	children.push_back(obj);
}

// Update the model view of our GameObject, recurse to the children.
// We need this even if a child isn't being rendered, in order to propagate the matrices correctly down the scene tree.
void GameObject::updateMV() {
	// Load up the MODELVIEW matrix for us to augment.
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	// If we have a transform to animate, let's apply it.
	AnimationComponent* ac = getComponent<AnimationComponent>();
	Transform result(transform);  // Same as our normal transform if no animation is present.
	if (ac) {
		Transform &target = ac->animatedTransform;
		result.scale = transform.scale * target.scale;
		result.translate = transform.translate + target.translate;
		result.angle = transform.angle + target.angle;
		result.angleAxis = target.angleAxis;  // We just overwrite out angleaxis from the animation.
	}
	
	// Apply the current transforms that will be applied to children (Scale doesnt apply to children)
	glTranslatef(result.translate.x, result.translate.y, result.translate.z);
	glRotatef(result.angle, result.angleAxis.x, result.angleAxis.y, result.angleAxis.z);

	// Loop through children and render them, building on the parent transforms as we recurse down the tree.
	for (size_t i = 0; i < children.size(); i++)
		children[i]->updateMV();

	// We don't want to scale our children, that's why this is down here after rendering the children.
	glScalef(result.scale.x, result.scale.y, result.scale.z);

	// Let the rendering system handle rendering.
	RenderingSystem::render(this);
	
	glPopMatrix(1); // Once we've rendered our object, we can dispose of our current matrix and move uo the hiearchy
}