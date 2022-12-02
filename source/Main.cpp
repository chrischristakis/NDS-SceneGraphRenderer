#include <nds.h>
#include <stdio.h>
#include <stdlib.h>
#include "Constants.h"
#include "Input/Input.h"
#include "Camera.h"

#include "SUS_pcx.h"
#include "texture_pcx.h"
#include "highres_pcx.h"
#include "lowres_pcx.h"
#include "ADT/GameObject.h"
#include "Components/MeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/ColorComponent.h"
#include "Components/TextureComponent.h"
#include "Components/AnimationComponent.h"
#include "Components/RenderingSystem.h"

GameObject *root;
GameObject *closeObject;
GameObject *orbitingObject;
GameObject *farObject;

void init() {
	consoleDemoInit();
	videoSetMode(MODE_0_3D);  // Main engine to use MODE 0 since we only need 1 3D background.
	vramSetBankA(VRAM_A_TEXTURE);
	
	glInit();  // Context time
	glClearColor(0, 2, 5, 31);
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

	closeObject = new GameObject("CloseObj", 0.0f, 0, 0.0f);
	// Initially an empty object without any components! Lets add some using our ecs down below.

	closeObject->addComponent<MeshComponent>(Constants::TRIANGLE_CUBE_VERTS,
		sizeof(Constants::TRIANGLE_CUBE_VERTS)/sizeof(float));
	closeObject->addComponent<TextureComponent>(SUS_pcx, TEXTURE_SIZE_128, Constants::TRIANGLE_CUBE_UVS,
		sizeof(Constants::TRIANGLE_CUBE_UVS) / sizeof(float));
	closeObject->addComponent<BoxComponent>(-1.0f, -1.0f, -1.0f, 2.0f, 2.0f, 2.0f);
	closeObject->addComponent<AnimationComponent>();

	// LOD loading happens here.
	closeObject->getComponent<MeshComponent>()->addLODMesh(10.0f, Constants::TRIANGLE_PYRAMID_VERTS,
		sizeof(Constants::TRIANGLE_PYRAMID_VERTS) / sizeof(float));
	closeObject->getComponent<TextureComponent>()->addLODTexture(10.0f, lowres_pcx, TEXTURE_SIZE_32,
		Constants::TRIANGLE_PYRAMID_UVS, sizeof(Constants::TRIANGLE_PYRAMID_UVS) / sizeof(float));

	// Handle transform animations for our gameobject.
	Transform *t1 = new Transform();
	t1->setScale(0.5f, 1.0f, 1.0f);
	closeObject->getComponent<AnimationComponent>()->addKeyframe(50, t1);
	Transform *t2 = new Transform();
	t2->setScale(1.0f, 0.5f, 1.0f);
	closeObject->getComponent<AnimationComponent>()->addKeyframe(100, t2);
	Transform *t3 = new Transform();
	t3->setScale(1.0f, 1.0f, 0.5f);
	closeObject->getComponent<AnimationComponent>()->addKeyframe(150, t3);
	Transform *t4 = new Transform();
	t4->setScale(1.0f, 1.0f, 1.0f);
	closeObject->getComponent<AnimationComponent>()->addKeyframe(200, t4);

	// Init orbiting object
	orbitingObject = new GameObject("Orbiter", 0.0f, 2.0f, 0.0f);
	orbitingObject->addComponent<MeshComponent>(Constants::TRIANGLE_QUAD_VERTS,
		sizeof(Constants::TRIANGLE_QUAD_VERTS)/sizeof(float));
	orbitingObject->addComponent<BoxComponent>(-1.0f, -1.0f, 0.0f, 2.0f, 2.0f, 0.0f);
	orbitingObject->transform.setScale(0.5f, 0.5f, 0.5f);
	orbitingObject->addComponent<TextureComponent>(SUS_pcx, TEXTURE_SIZE_128, Constants::TRIANGLE_QUAD_UVS,
		sizeof(Constants::TRIANGLE_QUAD_UVS) / sizeof(float));

	orbitingObject->getComponent<MeshComponent>()->addLODMesh(10.0f, Constants::TRIANGLE_QUAD_VERTS,
		sizeof(Constants::TRIANGLE_QUAD_VERTS) / sizeof(float));
	orbitingObject->getComponent<TextureComponent>()->addLODTexture(10.0f, lowres_pcx, TEXTURE_SIZE_32,
		Constants::TRIANGLE_QUAD_UVS, sizeof(Constants::TRIANGLE_QUAD_UVS) / sizeof(float));
	
	closeObject->addChild(orbitingObject);

	// Init far object
	farObject = new GameObject("FarObj", 5.0f, 0.0f, -20.0f);
	farObject->addComponent<MeshComponent>(Constants::TRIANGLE_CUBE_VERTS,
		sizeof(Constants::TRIANGLE_CUBE_VERTS) / sizeof(float));
	farObject->addComponent<BoxComponent>(-1.0f, -1.0f, 0.0f, 2.0f, 2.0f, 0.0f);
	farObject->addComponent<TextureComponent>(SUS_pcx, TEXTURE_SIZE_128, Constants::TRIANGLE_CUBE_UVS,
		sizeof(Constants::TRIANGLE_CUBE_UVS) / sizeof(float));

	farObject->getComponent<MeshComponent>()->addLODMesh(10.0f, Constants::TRIANGLE_CUBE_VERTS,
		sizeof(Constants::TRIANGLE_CUBE_VERTS) / sizeof(float));
	farObject->getComponent<TextureComponent>()->addLODTexture(10.0f, lowres_pcx, TEXTURE_SIZE_32,
		Constants::TRIANGLE_CUBE_UVS, sizeof(Constants::TRIANGLE_CUBE_UVS) / sizeof(float));

	farObject->addComponent<AnimationComponent>();
	Transform *t5 = new Transform();
	t5->setAngle(90, 0.0f, 1.0f, 0.0f);
	farObject->getComponent<AnimationComponent>()->addKeyframe(200, t5);
	Transform *t6 = new Transform();
	t6->setAngle(180, 1.0f, 0.0f, 0.0f);
	farObject->getComponent<AnimationComponent>()->addKeyframe(400, t6);
	Transform *t7 = new Transform();
	t7->setAngle(270, 0.0f, 0.0f, 1.0f);
	farObject->getComponent<AnimationComponent>()->addKeyframe(600, t7);
	Transform *t8 = new Transform();
	t8->setAngle(360, 0.0f, 1.0f, 0.0f);
	farObject->getComponent<AnimationComponent>()->addKeyframe(800, t8);

	root->addChild(closeObject);
	root->addChild(farObject);
}

int main() {
	init();
	initScene();
	
	int angle = 0;
	s16 x = 0, y = 0;

	Camera* &camera = RenderingSystem::camera;

	while (1) {
		GameObject::poly_counter = 0;  // Reset the amount of polygons drawn on each vblank.

		printf("\033[2J");
		printf("\nChris' 3D DS Engine");
		printf("\n-------------------");

		scanKeys();
		camera->updateInput();

		// Always gotta call this before our gameobject transforms in order to update the view matrix.
		camera->updateCamera();

		// Just used to show that we can alter transforms even if we're not using an animation.
		x = 2.5 * cosLerp(angle*300 % 32767);
		y = 2.5 * sinLerp(angle*300 % 32767);

		orbitingObject->transform.setTranslate(fixedToFloat(x, 12), fixedToFloat(y, 12), 0);
		angle++;

		// Render scene
		root->updateMV();

		printf("\n\nMAX: %d, RENDERED: %d", Constants::MAX_POLYGONS, GameObject::poly_counter);
		printf("\n\nCamera pos: %.4f, %.4f, %.4f", camera->position.x, camera->position.y, camera->position.z);

		glFlush(0);
		swiWaitForVBlank();
	}

	return 0;
}