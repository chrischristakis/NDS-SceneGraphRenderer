#include <nds.h>
#include <stdio.h>
#include "ADT/Object.h"
#include "ADT/Mesh.h"
#include "ADT/MeshObject.h"
#include "ADT/ColoredObject.h"
#include "ADT/TexturedObject.h"
#include "ADT/Transform.h"
#include "Constants.h"
#include "Input/Input.h"

#include "texture_pcx.h"
#include "ADT/GameObject.h"
#include "Components/MeshComponent.h"
#include "Components/BoxComponent.h"

GameObject *root;
GameObject *earth;
GameObject *moon;

void init() {
	consoleDemoInit();
	videoSetMode(MODE_0_3D);  // Main engine to use MODE 0 since we only need 1 3D background.
	vramSetBankA(VRAM_A_TEXTURE);
	
	glInit();  // Context time
	glClearColor(0, 2, 3, 31);
	glViewport(0, 0, 255, 191);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);

	glMatrixMode(GL_PROJECTION);	// We're about to establish our projection matrix.
	glLoadIdentity();	// Load in an identity matrix so we have a fresh slate.
	gluPerspective(90, 256.0 / 192.0, 0.1, 40);	// Our perspective projection, using an aspect ratio of our screen size

	Input::init();
}

// Our scenegraph goes here.
void initScene() {
	root = new GameObject("root", 0, 0, 0);  // The origin of our world.

	earth = new GameObject("Planet", 0.0f, 0, 0.0f);
	earth->addComponent<MeshComponent>(Constants::TRIANGLE_QUAD_VERTS,
		sizeof(Constants::TRIANGLE_QUAD_VERTS)/sizeof(float));
	earth->addComponent<BoxComponent>(-1.0f, -1.0f, 0.0f, 2.0f, 2.0f, 0.0f);

	moon = new GameObject("Moon", 0.0f, 2.0f, 0.0f);
	moon->addComponent<MeshComponent>(Constants::TRIANGLE_QUAD_VERTS, 
		sizeof(Constants::TRIANGLE_QUAD_VERTS)/sizeof(float));
	moon->addComponent<BoxComponent>(-1.0f, -1.0f, 0.0f, 2.0f, 2.0f, 0.0f);
	moon->transform.setScale(0.5f, 0.5f, 0.5f);

	earth->addChild(moon);
	earth->getComponent<MeshComponent>()->color.r = 0;

	root->addChild(earth);
}

int main() {
	init();
	initScene();
	
	int angle = 0;
	s16 x = 0, y = 0;
	
	struct CamPos {
		float x = 0;
		float y = 0;
		float z = -3.5f;
	} pos;

	while (1) {
		Object::poly_counter = 0;  // Reset out current polygon count each tick.
		GameObject::poly_counter = 0;  // Reset the amount of polygons drawn on each vblank.

		printf("\033[2J");
		printf("\n\nChris' 3D Renderer");

		scanKeys();
		if (Input::getButton("left"))
			pos.x += 0.05f;
		if (Input::getButton("right"))
			pos.x -= 0.05f;
		if (Input::getButton("up"))
			pos.z += 0.05f;
		if (Input::getButton("down"))
			pos.z -= 0.05f;
		if (Input::getButton("fire"))
			pos.y += 0.05f;
		if (Input::getButton("jump"))
			pos.y -= 0.05f;
		
		// Orbiting moon, still in fixed point 4.12
		x = 2.5 * cosLerp(angle*300 % 32767);
		y = 2.5 * sinLerp(angle*300 % 32767);

		earth->transform.setAngle(angle++, 0.0f, 1.0f, 0.0f);
		moon->transform.setTranslate(fixedToFloat(x, 12), fixedToFloat(y, 12), 0);

		//Camera transform
		root->transform.setTranslate(pos.x, pos.y, pos.z);

		// Render scene
		root->updateMV();

		printf("\n\nMax polygons: %d", Constants::MAX_POLYGONS);
		printf("\nRendered polygons: %d", GameObject::poly_counter);

		glFlush(0);
		swiWaitForVBlank();
	}

	return 0;
}