#ifndef RENDERINGSYSTEM_H
#define RENDERINGSYSTEM_H
#include "../ADT/GameObject.h"
#include "../Camera.h"

namespace RenderingSystem {
	extern Camera* camera;
	void render(GameObject* obj);
}

#endif