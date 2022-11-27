#include "ColorComponent.h"
#include <assert.h>

ColorComponent::ColorComponent(const uint8_t arr[], size_t N) {
	setVertexColors(arr, N);
}

void ColorComponent::setVertexColors(const uint8_t arr[], size_t N) {
	assert(N % 3 == 0);  // Since we're dealing with r,g,b pairs, we need to abide by this rule.
	vertColors.assign(arr, arr + N);
}