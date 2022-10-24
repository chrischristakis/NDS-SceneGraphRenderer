#include <nds.h>
#include <stdio.h>
#include "ADT/Mesh.h"
#include "ADT/MeshObject.h"
#include "Constants.h"
#include "ADT/Transform.h"

void init() {
	consoleDemoInit();
	videoSetMode(MODE_0_3D);  // Main engine to use MODE 0 since we only need 1 3D background.
	
	glInit();  // Context time
	glClearColor(0, 2, 3, 31);

	glMatrixMode(GL_PROJECTION);	// We're about to establish our projection matrix.
	glLoadIdentity();	// Load in an identity matrix so we have a fresh slate.
	gluPerspective(90, 256.0 / 192.0, 0.1, 40);	// Our perspective projection, using an aspect ratio of our screen size
}

int main() {
	init();

	Mesh *m = new Mesh{ Constants::CUBE_VERTS, sizeof(Constants::CUBE_VERTS) / sizeof(float), GL_QUAD };
	MeshObject mo{ m, 0.0f, 0.0f, 0.0f};
	MeshObject *mo1 = new MeshObject(m, 0.0f, 0.0f, -3.5f);

	//The parent of Mo is Mo1, meaning Mo's transforms are RLEATIVE to Mo1.
	mo.parent = mo1;

	mo.transform.setScale(0.5f, 0.5f, 0.5f);

	int angle = 0;
	s16 x = 0, y = 0;
	mo.setColor(50, 50, 50);
	mo1->setColor(7, 55, 255);

	while (1) {
		printf("\033[2J");
		printf("\n\n3D Scene graph renderer");
		printf("\nx: %.3f, y: %.3f", fixedToFloat(x, 12), fixedToFloat(y, 12));
		glPolyFmt(POLY_ALPHA(31) | POLY_CULL_NONE | POLY_FORMAT_LIGHT0);

		// Orbiting moon
		x = 1.5 * cosLerp(angle*300 % 32767);
		y = 1.5 * sinLerp(angle*300 % 32767);

		mo.transform.setTranslate(fixedToFloat(x, 12), fixedToFloat(y, 12), 0);
		mo.render();

		mo1->transform.setAngle(angle++, 1.0f, 1.0f, 0.0f);
		mo1->render();

		glFlush(0);
		swiWaitForVBlank();
	}

	return 0;
}