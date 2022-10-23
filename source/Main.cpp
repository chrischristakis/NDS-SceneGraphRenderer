#include <nds.h>
#include <stdio.h>
#include "ADT/Mesh.h"
#include "Constants.h"

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

	Mesh m{ Constants::CUBE_VERTS, sizeof(Constants::CUBE_VERTS) / sizeof(float), GL_QUAD };

	int angle = 0;
	while (1) {
		printf("\033[2J");
		printf("\n\n 3D Scene graph renderer");

		glPolyFmt(POLY_ALPHA(31) | POLY_CULL_NONE | POLY_FORMAT_LIGHT0);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0, 0, -3.0f);
		glRotatef(angle++, 0, 1.0f, 0);

		glBegin(m.draw_mode);
			glColor3f(1.0f, 0.0f, 0.0f);
			for (size_t i = 0; i < m.vertices.size(); i+=3)
				glVertex3f(m.vertices[i], m.vertices[i+1], m.vertices[i+2]);
		glEnd();

		glFlush(0);
		swiWaitForVBlank();
	}

	return 0;
}