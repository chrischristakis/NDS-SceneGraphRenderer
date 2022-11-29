#include <nds.h>
#include <stdio.h>
#include "Constants.h"
#include "Input/Input.h"
#include "Camera.h"

#include "SO_SUS_pcx.h"
#include "ADT/GameObject.h"
#include "Components/MeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/ColorComponent.h"
#include "Components/TextureComponent.h"
#include "Components/AnimationComponent.h"

GameObject *root;
GameObject *earth;
GameObject *moon;

Camera camera;

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

	//Change our virtual inputs to our uses
	Input::swapButtonName("fire", "forward");
	Input::swapButtonName("jump", "backward");
}

// Our scenegraph goes here.
void initScene() {
	root = new GameObject("root", 0, 0, 0);  // The origin of our world.

	earth = new GameObject("Planet", 0.0f, 0, 0.0f);
	earth->addComponent<MeshComponent>(Constants::TRIANGLE_CUBE_VERTS,
		sizeof(Constants::TRIANGLE_CUBE_VERTS)/sizeof(float));
	earth->addComponent<BoxComponent>(-1.0f, -1.0f, -1.0f, 2.0f, 2.0f, 2.0f);
	earth->addComponent<AnimationComponent>();

	// Handle transform animations
	Transform *t1 = new Transform();
	t1->setScale(0.5f, 1.0f, 1.0f);
	//t1->setAngle(90, 0.0f, 1.0f, 0.0f);
	earth->getComponent<AnimationComponent>()->addKeyframe(50, t1);
	Transform *t2 = new Transform();
	t2->setScale(1.0f, 0.5f, 1.0f);
	//t2->setAngle(180, 0.0f, 1.0f, 0.0f);
	earth->getComponent<AnimationComponent>()->addKeyframe(100, t2);
	Transform *t3 = new Transform();
	t3->setScale(1.0f, 1.0f, 0.5f);
	//t3->setAngle(270, 0.0f, 1.0f, 0.0f);
	earth->getComponent<AnimationComponent>()->addKeyframe(150, t3);
	Transform *t4 = new Transform();
	t4->setScale(1.0f, 1.0f, 1.0f);
	//t4->setAngle(360, 0.0f, 1.0f, 0.0f);
	earth->getComponent<AnimationComponent>()->addKeyframe(200, t4);


	moon = new GameObject("Moon", 0.0f, 2.0f, 0.0f);
	moon->addComponent<MeshComponent>(Constants::TRIANGLE_QUAD_VERTS, 
		sizeof(Constants::TRIANGLE_QUAD_VERTS)/sizeof(float));
	moon->addComponent<BoxComponent>(-1.0f, -1.0f, 0.0f, 2.0f, 2.0f, 0.0f);
	moon->transform.setScale(0.5f, 0.5f, 0.5f);
	moon->addComponent<TextureComponent>(SO_SUS_pcx, TEXTURE_SIZE_128, Constants::TRIANGLE_QUAD_UVS,
		sizeof(Constants::TRIANGLE_QUAD_UVS) / sizeof(float));
	
	earth->addChild(moon);
	root->addChild(earth);
}

int main() {
	init();
	initScene();
	
	int angle = 0;
	s16 x = 0, y = 0;

	while (1) {
		GameObject::poly_counter = 0;  // Reset the amount of polygons drawn on each vblank.

		printf("\033[2J");
		printf("\nChris' 3D DS Engine");
		printf("\n-------------------");

		scanKeys();
		camera.updateInput();

		// Always gotta call this before our gameobject transforms
		camera.updateCamera();

		// Orbiting moon, still in fixed point 4.12
		x = 2.5 * cosLerp(angle*300 % 32767);
		y = 2.5 * sinLerp(angle*300 % 32767);

		//earth->transform.setAngle(angle, 0.0f, 1.0f, 0.0f);
		moon->transform.setTranslate(fixedToFloat(x, 12), fixedToFloat(y, 12), 0);
		angle++;

		// Render scene
		root->updateMV();

		printf("\n\nMAX: %d, RENDERED: %d", Constants::MAX_POLYGONS, GameObject::poly_counter);

		glFlush(0);
		swiWaitForVBlank();
	}

	return 0;
}