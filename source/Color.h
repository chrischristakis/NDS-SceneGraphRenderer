#ifndef COLOR_H
#define COLOR_H

// Values: [0-1]
struct Color3f {
	float r, g, b;
	Color3f(float r, float g, float b): r(r), g(g), b(b) {}
	Color3f(): r(0), g(0), b(0) {}
};

// Values: [0-255]
struct Color3b {
	int r, g, b;
	Color3b(int r, int g, int b) : r(r), g(g), b(b) {}
	Color3b() : r(0), g(0), b(0) {}
};

#endif