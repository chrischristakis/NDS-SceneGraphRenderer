#ifndef TEXTURECOMPONENT_H
#define TEXTURECOMPONENT_H
#include <vector>
#include <map>
#include <nds.h>
#include "Component.h"

struct Texture {
	std::vector<float> uvs;
	int textureID;  // Used for our opengl context to assign a texture to.

	Texture(const uint8_t* pcx, GL_TEXTURE_SIZE_ENUM img_size, const float uvs[], size_t N);
};

struct TextureComponent : public Component {

	std::map<float, Texture*> textures;

	~TextureComponent();

	TextureComponent(const uint8_t* pcx, GL_TEXTURE_SIZE_ENUM img_size, const float uvs[], size_t N);
	void addLODTexture(float distance, const uint8_t* pcx, GL_TEXTURE_SIZE_ENUM img_size, const float uvs[], size_t N);
	
};

#endif 