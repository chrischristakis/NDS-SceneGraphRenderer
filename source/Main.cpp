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
#include "Components/Color.h"

Object* root;
ColoredObject* cube;
TexturedObject* quad;
MeshObject* plane;
Mesh *cube_mesh;
Mesh *quad_mesh;

GameObject *test;

void init() {
	consoleDemoInit();
	videoSetMode(MODE_0_3D);  // Main engine to use MODE 0 since we only need 1 3D background.
	vramSetBankA(VRAM_A_TEXTURE);
	
	glInit();  // Context time
	glClearColor(0, 2, 3, 31);
	glViewport(0, 0, 255, 191);
	glEnable(GL_TEXTURE_2D);

	glMatrixMode(GL_PROJECTION);	// We're about to establish our projection matrix.
	glLoadIdentity();	// Load in an identity matrix so we have a fresh slate.
	gluPerspective(90, 256.0 / 192.0, 0.1, 40);	// Our perspective projection, using an aspect ratio of our screen size

	Input::init();
}

// Our scenegraph goes here.
void initScene() {
	root = new Object("root", 0, 0, 0);  // The origin of our world.

	cube_mesh = new Mesh{ -0.5f, -0.5f, -0.5f, 1, 1, 1,
		Constants::CUBE_VERTS, sizeof(Constants::CUBE_VERTS) / sizeof(float), DrawMode::QUAD };

	quad_mesh = new Mesh{ -0.5, -0.5, 0.0f, 1, 1, 0, 
		Constants::QUAD_VERTS, sizeof(Constants::QUAD_VERTS) / sizeof(float), DrawMode::QUAD };

	cube = new ColoredObject{"Planet", cube_mesh, Constants::CUBE_COLORS, sizeof(Constants::CUBE_COLORS)/sizeof(byte),
		0.0f, 0.0f, 0.0f};
	quad = new TexturedObject("AMONGUS", quad_mesh, texture_pcx, TEXTURE_SIZE_128, Constants::AMONG_US_QUAD_UV,
		sizeof(Constants::AMONG_US_QUAD_UV) / sizeof(float),
		0.0f, 0.0f, 0.0f);
	plane = new MeshObject{ "Plane", quad_mesh, 0, -3.5f, 0 };

	plane->transform.setAngle(90, 1.0f, 0.0f, 0.0f);
	plane->transform.setScale(10.0f, 10.0f, 0);

	cube->addChild(quad);

	root->addChild(cube);
	root->addChild(plane);

	test = new GameObject();
	test->addComponent<Color>(10, 10, 10);
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
		if (Input::getButton("start"))
			root->removeChild(quad);
		
		// Orbiting moon
		x = 1.5 * cosLerp(angle*300 % 32767);
		y = 1.5 * sinLerp(angle*300 % 32767);

		// Independent transforms
		if(quad)
			quad->transform.setTranslate(fixedToFloat(x, 12), fixedToFloat(y, 12), 0);

		cube->transform.setAngle(angle++, 0.0f, 1.0f, 0.0f);

		//Camera transform
		root->transform.setTranslate(pos.x, pos.y, pos.z);

		// Render scene
		root->updateAndRender();

		printf("\n\nMax polygons: %d", Object::MAX_POLYS);
		printf("\nRendered polygons: %d", Object::poly_counter);
		Color* componentCol = test->getComponent<Color>();
		printf("\nTest component: %d %d %d", componentCol->r++, componentCol->g, componentCol->b);

		glFlush(0);
		swiWaitForVBlank();
	}

	return 0;
}