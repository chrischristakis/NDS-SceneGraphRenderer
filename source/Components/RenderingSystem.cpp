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

Camera* RenderingSystem::camera = new Camera(0, 0, 5.0f);

// Hoisting time
void drawMesh(Mesh* mesh);
void drawColoredMesh(Mesh* mesh, Color* colorComponent);
void drawTexturedMesh(Mesh* mesh, Texture* tex);

void RenderingSystem::render(GameObject* obj) {
	if (!obj) return;

	//Update our animation component
	AnimationComponent* ac = obj->getComponent<AnimationComponent>();
	if (ac)
		ac->update();

	MeshComponent* meshComponent = obj->getComponent<MeshComponent>();
	bool bounded = true;
	printf("\n\"%s\": ", obj->name.c_str());

	// Only render if we have a mesh component to render
	if (meshComponent) {
		float cameraDistanceToObject = Vector3f::distance(camera->position, obj->transform.translate);
		
		// One big downside to this LOD implementation is that we have to manually (as the user) make sure that 
		// if this is a texutred or colored mesh, the keys (distances) in the texture/color and mesh match. There's ways around
		// this obviously, and with a little bit of infrastructure tuning this wouldn't be an issue. But because I'm
		// working on this at the tail end of the assignment, it is what it is.
		float lodIndex = 0;

		// If we're far enough to use a lower LOD mesh, go with that.
		for (auto it = meshComponent->meshes.begin(); it != meshComponent->meshes.end(); it++) {
			if (cameraDistanceToObject >= it->first)  // If our camera's distance exceeds the furthest LOD mesh, use it! We can do this since maps are ordered on their key (distance)
				lodIndex = it->first;
		}

		printf("LOD: %.3f ", lodIndex);

		Mesh* mesh = meshComponent->meshes[lodIndex];  // Use the mesh with our associated distance.

		if (GameObject::poly_counter + mesh->polys <= Constants::MAX_POLYGONS) {

			// Frustum culling
			BoxComponent* boundingBox = obj->getComponent<BoxComponent>();
			if (boundingBox)
				bounded = boundingBox->bounded();

			if (bounded) {
				GameObject::poly_counter += mesh->polys;

				ColorComponent* colorComponent = obj->getComponent<ColorComponent>();
				TextureComponent* texComponent = obj->getComponent<TextureComponent>();
				if (texComponent) { // Texture components take priority should some silly person assign both color and texture.

					// Use our mesh LOD to index which texture to use. This very fickle line of code is the crux of the 
					// very unintuitive solution I talked about above.
					Texture* tex = texComponent->textures[lodIndex];

					drawTexturedMesh(mesh, tex);
				}
				else if (colorComponent) {
					Color* col = colorComponent->colors[lodIndex];
					drawColoredMesh(mesh, col);
				}
				else
					drawMesh(mesh);

				printf("rendered");
			}
		}
	}
}

void drawTexturedMesh(Mesh* mesh, Texture* tex) {
	glPolyFmt(POLY_ALPHA(31) | mesh->culling | POLY_FORMAT_LIGHT1);

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

void drawColoredMesh(Mesh* mesh, Color* col) {
	glPolyFmt(POLY_ALPHA(31) | mesh->culling | POLY_FORMAT_LIGHT0);
	auto &vertices = mesh->vertices;
	auto &vertColors = col->vertColors;

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
void drawMesh(Mesh* mesh) {
	glPolyFmt(POLY_ALPHA(31) | mesh->culling | POLY_FORMAT_LIGHT0);
	auto &vertices = mesh->vertices;

	glBegin(GL_TRIANGLES);
		glColor3b(mesh->color.r, mesh->color.g, mesh->color.b);
		for (size_t i = 0; i < vertices.size(); i += 3)
			glVertex3f(vertices[i], vertices[i + 1], vertices[i + 2]);
	glEnd();
}