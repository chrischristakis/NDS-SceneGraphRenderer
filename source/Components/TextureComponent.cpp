#include "TextureComponent.h"
TextureComponent::TextureComponent(const uint8_t* pcx, GL_TEXTURE_SIZE_ENUM img_size, const float uvs[], size_t N) {
	this->uvs.assign(uvs, uvs + N);

	sImage pcx_temp;  // Use this to store pcx data temporarily until we generate a texture
	loadPCX((u8*)pcx, &pcx_temp);  // Put data in our sImage I guess.
	image8to16(&pcx_temp);  // 8 bpp to 16 bpp 

	glGenTextures(1, &textureID);
	glBindTexture(0, textureID);
	glTexImage2D(0, 0, GL_RGB, img_size, img_size, 0, TEXGEN_TEXCOORD, pcx_temp.image.data8);
	glBindTexture(GL_TEXTURE_2D, 0);  // If we don't unbind, everything will be dark.

	imageDestroy(&pcx_temp);
}