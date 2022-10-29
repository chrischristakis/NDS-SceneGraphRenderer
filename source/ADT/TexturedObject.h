#ifndef TEXTUREDOBJECT_H
#define TEXTUREDOBJECT_H
#include <vector>
#include <string>
#include <stdint.h>
#include <nds.h>
#include "Mesh.h"
#include "Object.h"

struct TexturedObject : public Object {
	std::vector<float> uvs;
	int texID;  // Used to both set and rerieve image data from our OGL context.

	TexturedObject(Mesh* mesh, const uint8_t* pcx, GL_TEXTURE_SIZE_ENUM img_size,
		const float uvs[], size_t N, 
		float x, float y, float z);
	TexturedObject(std::string name, Mesh* mesh, const uint8_t* pcx, GL_TEXTURE_SIZE_ENUM img_size,
		const float uvs[], size_t N,
		float x, float y, float z);

	void render();
};

#endif