#include "ColorComponent.h"
#include <assert.h>

Color::Color(const uint8_t arr[], size_t N) {
	setVertexColors(arr, N);
}

void Color::setVertexColors(const uint8_t arr[], size_t N) {
	assert(N % 3 == 0);  // Since we're dealing with r,g,b pairs, we need to abide by this rule.
	vertColors.assign(arr, arr + N);
}

ColorComponent::ColorComponent(const uint8_t arr[], size_t N) {
	colors.insert({ 0, new Color(arr, N) });
}

void ColorComponent::addLODColor(float distance, const uint8_t arr[], size_t N) {
	colors.insert({ distance, new Color(arr, N) });
}

ColorComponent::~ColorComponent() {
	for (auto it = colors.begin(); it != colors.end(); it++)
		delete it->second;
	colors.clear();
}