#ifndef BOX_H
#define BOX_H

struct Box {
	float x, y, z;  // Describes 'back bottom left' vertex
	float width, height, depth;

	Box() = default;
	Box(float x, float y, float z, float width, float height, float depth)
		: x(x), y(y), z(z), width(width), height(height), depth(depth) {}

	void render();
	bool bounded();  // True if on screen, false if off screen.
};

#endif