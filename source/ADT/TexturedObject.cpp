#include "TexturedObject.h"
#include <assert.h>


TexturedObject::TexturedObject(Mesh* mesh, const uint8_t* pcx, GL_TEXTURE_SIZE_ENUM img_size,
		const float uvs[], size_t N, float x, float y, float z)
		: Object(x, y, z) {
	
	assert(mesh->vertices.size() / 3 == N / 2);  // 3 points per vert, 2 uvs per vert.

	addMesh(mesh);
	this->uvs.assign(uvs, uvs + N);

	sImage pcx_temp;
	loadPCX((u8*) pcx, &pcx_temp);
	image8to16(&pcx_temp);  // 8 bpp to 16 bpp

	glGenTextures(1, &texID);
	glBindTexture(0, texID);
	glTexImage2D(0, 0, GL_RGB, img_size, img_size, 0, TEXGEN_TEXCOORD, pcx_temp.image.data8);

	imageDestroy(&pcx_temp);

}

TexturedObject::TexturedObject(std::string name, Mesh* mesh, const uint8_t* pcx, GL_TEXTURE_SIZE_ENUM img_size,
		const float uvs[], size_t N, float x, float y, float z)
		 : TexturedObject(mesh, pcx, img_size, uvs, N, x, y, z) {
	this->name = name;
}

void TexturedObject::render() {
	glPolyFmt(POLY_ALPHA(31) | POLY_CULL_NONE | POLY_FORMAT_LIGHT1);

	glBindTexture(0, texID);

	glBegin(mesh->draw_mode);
	glColor3f(1.0f, 1.0f, 1.0f);
	std::vector<float> &vertices = mesh->vertices;
	int texIndex = 0;
	for (size_t i = 0; i < vertices.size(); i += 3) {
		glTexCoord2f(uvs[texIndex], 1.0f - uvs[texIndex+1]);  // Image is flipped for some reason in OPENGL hence the 1.0f - 
		glVertex3f(vertices[i], vertices[i + 1], vertices[i + 2]);
		texIndex+=2;
	}
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0); // We need to bind the default texture, otherwise everything else in the scene will be dark.
	// why.


}