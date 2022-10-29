#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <nds/arm9/videoGL.h>

namespace Constants {
	const float TRIANGLE_VERTS[] = {
		-0.5f, -0.5f,  0.0f,
		 0.5f, -0.5f,  0.0f,
		 0.0f,  0.5f,  0.0f
	};

	const float QUAD_VERTS[] = {
		-0.5f, -0.5f,  0.0f, //bl
		 0.5f, -0.5f,  0.0f, //br
		 0.5f,  0.5f,  0.0f, //tr
		-0.5f,  0.5f,  0.0f, //tl
	};

	const float AMONG_US_QUAD_UV[] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f
	};

	const float CUBE_VERTS[] = {
		//front face
		-0.5f, -0.5f,  0.5f, //bl
		 0.5f, -0.5f,  0.5f, //br
		 0.5f,  0.5f,  0.5f, //tr
		-0.5f,  0.5f,  0.5f, //tl

		//back face
		-0.5f, -0.5f, -0.5f, 
		-0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,

		//top face
		-0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f, 
		 0.5f,  0.5f, -0.5f, 
		-0.5f,  0.5f, -0.5f,

		//bot face
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f, 
		 0.5f, -0.5f, -0.5f, 
		 0.5f, -0.5f,  0.5f,

		//left face
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		
		//right face
		 0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,
	};

	const byte CUBE_COLORS[] = {
		255, 0, 0,
		0, 255, 0,
		0, 0, 255,
		255, 0, 255,

		255, 0, 255,
		0, 255, 0,
		255, 0, 100,
		100, 0, 0,

		0, 0, 0,
		255, 255, 255,
		40, 40, 40,
		150, 150, 150,

		255, 100, 10,
		0, 255, 255,
		255, 255, 0,
		255, 255, 0,

		255, 0, 0,
		0, 255, 0,
		0, 0, 255,
		255, 0, 255,

		255, 0, 0,
		0, 255, 0,
		0, 255, 0,
		255, 0, 255,
	};
}

// Specify how many vertices we need to draw one polygon of this shape
enum class DrawMode {
	TRIANGLES = 3,
	QUAD = 4
};

#endif