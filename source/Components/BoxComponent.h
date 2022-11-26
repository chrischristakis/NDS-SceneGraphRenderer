#ifndef BOXCOMPONENT_H
#define BOXCOMPONENT_H
#include "Component.h"

struct BoxComponent : public Component {
	float x, y, z;  // Origin position, using the right hand rule.
	float width, height, depth;

	BoxComponent(float x, float y, float z, float width, float height, float depth)
		: x(x), y(y), z(z), width(width), height(height), depth(depth) {}

	void render();
	bool bounded();  // True if on screen, false if off screen.
};

#endif