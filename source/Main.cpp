#include <nds.h>
#include <stdio.h>
#include "ADT/Mesh.h"
#include "ADT/MeshObject.h"
#include "Constants.h"
#include "ADT/Transform.h"

Object* root;
MeshObject* mo;
MeshObject* mo1;
Mesh *m;

void init() {
	consoleDemoInit();
	videoSetMode(MODE_0_3D);  // Main engine to use MODE 0 since we only need 1 3D background.
	
	glInit();  // Context time
	glClearColor(0, 2, 3, 31);
	glViewport(0, 0, 255, 191);

	glMatrixMode(GL_PROJECTION);	// We're about to establish our projection matrix.
	glLoadIdentity();	// Load in an identity matrix so we have a fresh slate.
	gluPerspective(90, 256.0 / 192.0, 0.1, 40);	// Our perspective projection, using an aspect ratio of our screen size
}

// Our scenegraph goes here.
void initScene() {
	root = new Object("root", 0, 0, 0);  // The origin of our world.

	m = new Mesh{ -0.5f, -0.5f, -0.5f, 1, 1, 1,
		Constants::CUBE_VERTS, sizeof(Constants::CUBE_VERTS) / sizeof(float), GL_QUAD };

	mo = new MeshObject{"Moon", m, 0.0f, 0.0f, 0.0f};
	mo1 = new MeshObject(m, 0.0f, 0.0f, -3.5f);

	mo1->addChild(mo);
	root->addChild(mo1);

	mo->transform.setScale(0.5f, 0.5f, 0.5f);
	mo->setColor(50, 50, 50);
	mo1->setColor(7, 55, 255);
}

int main() {
	init();
	initScene();
	
	int angle = 0;
	s16 x = 0, y = 0;
	float px = 0, pz = -3.5f;

	while (1) {

		printf("\033[2J");
		printf("\n\nChris' 3D Scene graph renderer");

		scanKeys();
		int keys = keysHeld();
		if (keys & KEY_LEFT)
			px += 0.05f;
		if (keys & KEY_RIGHT)
			px -= 0.05f;
		if (keys & KEY_UP)
			pz += 0.05f;
		if (keys & KEY_DOWN)
			pz -= 0.05f;
		if (keys & KEY_A)
			root->removeChild(mo);
		
		// Orbiting moon
		x = 1.5 * cosLerp(angle*300 % 32767);
		y = 1.5 * sinLerp(angle*300 % 32767);

		if(mo)
			mo->transform.setTranslate(fixedToFloat(x, 12), fixedToFloat(y, 12), 0);

		mo1->transform.setAngle(angle++, 1.0f, 1.0f, 0.0f);
		mo1->transform.setTranslate(px, mo1->transform.translate.y, pz);

		root->renderSelfAndChildren();

		glFlush(0);
		swiWaitForVBlank();
	}

	return 0;
}