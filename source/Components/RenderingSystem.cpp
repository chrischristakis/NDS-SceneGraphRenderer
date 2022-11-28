#include <nds.h>
#include "RenderingSystem.h"
#include "MeshComponent.h"
#include "BoxComponent.h"
#include "ColorComponent.h"
#include "TextureComponent.h"
#include "AnimationComponent.h"
#include "../Constants.h"
#include <vector>
#include <assert.h>

// Hoisting time
void drawMesh(MeshComponent* mesh);
void drawColoredMesh(MeshComponent* mesh, ColorComponent* colorComponent);
void drawTexturedMesh(MeshComponent* mesh, TextureComponent* tex);

void RenderingSystem::render(GameObject* obj) {
	if (!obj) return;

	//Update our animation component
	AnimationComponent* ac = obj->getComponent<AnimationComponent>();
	if (ac)
		ac->update();

	MeshComponent* mesh = obj->getComponent<MeshComponent>();
	bool bounded = true;
	printf("\n[\"%s\", ID:%d] ", obj->name.c_str(), obj->ID);
	if (mesh) {
		if (GameObject::poly_counter + mesh->polys <= Constants::MAX_POLYGONS) {
			BoxComponent* boundingBox = obj->getComponent<BoxComponent>();
			if (boundingBox)
				bounded = boundingBox->bounded();

			if (bounded) {
				GameObject::poly_counter += mesh->polys;

				ColorComponent* colorComponent = obj->getComponent<ColorComponent>();
				TextureComponent* texComponent = obj->getComponent<TextureComponent>();
				if (texComponent) { // Texture components take priority should some silly person assign both color and texture.
					drawTexturedMesh(mesh, texComponent);
				}
				else if (colorComponent)
					drawColoredMesh(mesh, colorComponent);
				else
					drawMesh(mesh);

				printf("rendered");
			}
			else
				printf("unrendered");
		}
	}
}

void drawTexturedMesh(MeshComponent* mesh, TextureComponent* tex) {
	glPolyFmt(POLY_ALPHA(31) | POLY_CULL_NONE | POLY_FORMAT_LIGHT1);

	auto &vertices = mesh->vertices;
	auto &uvs = tex->uvs;
	int texIndex = 0;
	glBindTexture(0, tex->textureID);
	
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 1.0f, 1.0f);
	for (size_t i = 0; i < vertices.size(); i += 3) {
		glTexCoord2f(uvs[texIndex], 1.0f - uvs[texIndex+1]);  // Image is flipped for some reason in OGL hence the 1.0f - 
		glVertex3f(vertices[i], vertices[i + 1], vertices[i + 2]);
		texIndex += 2;  // UV index, increment by 2 to iterate
	}
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0); // We need to bind the default texture, otherwise everything else in the scene will be dark.
	// I still dont get why without this everything is darker. When I tell you I spent 2 hours debugging this I'm not joking.

}

void drawColoredMesh(MeshComponent* mesh, ColorComponent* colorComponent) {
	glPolyFmt(POLY_ALPHA(31) | POLY_CULL_NONE | POLY_FORMAT_LIGHT0);
	auto &vertices = mesh->vertices;
	auto &vertColors = colorComponent->vertColors;

	// 3 colors per vert, 3 positions per vert, so our sizes must match for a color to be properly applied.
	assert(vertColors.size() == vertices.size());

	glBegin(GL_TRIANGLES);
	for (size_t i = 0; i < vertices.size(); i += 3) {
		glColor3b(vertColors[i], vertColors[i + 1], vertColors[i + 2]);
		glVertex3f(vertices[i], vertices[i + 1], vertices[i + 2]);
	}
	glEnd();
}

// Basic mesh render of a uniform colour.
void drawMesh(MeshComponent* mesh) {
	glPolyFmt(POLY_ALPHA(31) | POLY_CULL_NONE | POLY_FORMAT_LIGHT0);
	auto &vertices = mesh->vertices;

	glBegin(GL_TRIANGLES);
		glColor3b(mesh->color.r, mesh->color.g, mesh->color.b);
		for (size_t i = 0; i < vertices.size(); i += 3)
			glVertex3f(vertices[i], vertices[i + 1], vertices[i + 2]);
	glEnd();
}