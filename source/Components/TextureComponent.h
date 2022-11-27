#ifndef TEXTURECOMPONENT_H
#define TEXTURECOMPONENT_H
#include <vector>
#include <nds.h>
#include "Component.h"

struct TextureComponent : public Component {

	std::vector<float> uvs;
	int textureID;  // Used for our opengl context to assign a texture to.

	TextureComponent(const uint8_t* pcx, GL_TEXTURE_SIZE_ENUM img_size, const float uvs[], size_t N);
	
};

#endif 