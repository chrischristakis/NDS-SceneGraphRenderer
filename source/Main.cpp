#include <nds.h>
#include <stdio.h>

void init() {
	consoleDemoInit();
	videoSetMode(MODE_0_3D);  // Main engine to use MODE 0 since we only need 1 3D background.
	
	glInit();  // Context time
	glClearColor(0, 2, 3, 31);

	glMatrixMode(GL_PROJECTION);	// We're about to establish our projection matrix.
	glLoadIdentity();	// Load in an identity matrix so we have a fresh slate.
	gluPerspective(70, 256.0 / 192.0, 0.1, 40);	// Our perspective projection, using an aspect ratio of our screen size
}

int main() {
	init();

	while (1) {
		printf("\033[2J");
		printf("\n\n 3D Scene graph renderer");

		glPolyFmt(POLY_ALPHA(31) | POLY_CULL_NONE | POLY_FORMAT_LIGHT0);

		glBegin(GL_TRIANGLE);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(-0.5f, -0.5f, -1.0f);
			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(0.5f, -0.5f, -1.0f);
			glColor3f(0.0f, 0.0f, 1.0f);
			glVertex3f(0.0f, 0.5f, -1.0f);
		glEnd();

		glFlush(0);
		swiWaitForVBlank();
	}

	return 0;
}