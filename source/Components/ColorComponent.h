#ifndef COLORCOMPONENT_H
#define COLORCOMPONENT_H
#include"Component.h"
#include <vector>
#include <nds.h>

struct ColorComponent : public Component {
	// 3 colors components per vertex (r,g,b), should have same size as the mesh vertex array.
	// Using the arbitrary choice of storing colors from 0-255 (byte) instead of as a float.
	std::vector<uint8_t> vertColors;

	ColorComponent(const uint8_t arr[], size_t N);
	void setVertexColors(const uint8_t arr[], size_t N);
};

#endif