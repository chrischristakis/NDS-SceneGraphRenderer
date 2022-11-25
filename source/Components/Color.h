#pragma once
#include "Component.h"

struct Color : public Component {
	int r, g, b;
	Color(int r, int g, int b): r(r), g(g), b(b) {}
};