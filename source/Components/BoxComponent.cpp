#include "BoxComponent.h"
#include <nds/arm9/videoGL.h>
#include <nds/arm9/boxtest.h>

// Draw a bounding box for debugging.
void BoxComponent::render() {

	glPolyFmt(POLY_ALPHA(10) | POLY_CULL_NONE | POLY_FORMAT_LIGHT0);

	glBegin(GL_QUADS);

	glColor3b(255, 0, 0);
	glVertex3f(x, y, z);
	glVertex3f(x, y + height, z);
	glVertex3f(x + width, y + height, z);
	glVertex3f(x + width, y, z);

	glVertex3f(x + width, y, z);
	glVertex3f(x + width, y + height, z);
	glVertex3f(x + width, y + height, z + depth);
	glVertex3f(x + width, y, z + depth);

	glVertex3f(x, y, z + depth);
	glVertex3f(x + width, y, z + depth);
	glVertex3f(x + width, y + height, z + depth);
	glVertex3f(x, y + height, z + depth);

	glVertex3f(x, y, z);
	glVertex3f(x, y, z + depth);
	glVertex3f(x, y + height, z + depth);
	glVertex3f(x, y + height, z);

	glVertex3f(x, y + height, z);
	glVertex3f(x, y + height, z + depth);
	glVertex3f(x + width, y + height, z + depth);
	glVertex3f(x + width, y + height, z);

	glVertex3f(x, y, z);
	glVertex3f(x + width, y, z);
	glVertex3f(x + width, y, z + depth);
	glVertex3f(x, y, z + depth);

	glEnd();
}

bool BoxComponent::bounded() {
	// We need the ternerary op since Boxtest returns any non zero number, not just 0 or 1
	return BoxTestf(x, y, z, width, height, depth) ? true : false;
}