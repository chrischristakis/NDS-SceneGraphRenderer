#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <nds/arm9/videoGL.h>

namespace Constants {

	const int MAX_POLYGONS = 4000;

	const float TRIANGLE_VERTS[] = {
		-0.5f, -0.5f,  0.0f,
		 0.5f, -0.5f,  0.0f,
		 0.0f,  0.5f,  0.0f
	};

	const float TRIANGLE_QUAD_VERTS[] = {
		-1.0f, -1.0f,  0.0f,
		 1.0f, -1.0f,  0.0f,
		 1.0f,  1.0f,  0.0f,

		 1.0f,  1.0f,  0.0f,
		-1.0f,  1.0f,  0.0f,
		-1.0f, -1.0f,  0.0f,
	};

	const uint8_t TRIANGLE_QUAD_COLORS[] = {
		255, 0, 0,
		0, 255, 0,
		0, 0, 255,

		0, 0, 255,
		0, 255, 0,
		255, 0, 0,
	};

	const float TRIANGLE_QUAD_UVS[] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,

		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f
	};

	const float TRIANGLE_CUBE_VERTS[] = {
		//front face
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,

		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		//back face
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,

		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,

		//left face
		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,

		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,

		//right face
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,

		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,

		 //top face
		 -1.0f, 1.0f, -1.0f,
		 -1.0f, 1.0f,  1.0f,
		  1.0f, 1.0f,  1.0f,

		  1.0f, 1.0f,  1.0f,
		  1.0f, 1.0f, -1.0f,
		 -1.0f, 1.0f, -1.0f,

		 //bottom face
		 -1.0f, -1.0f, -1.0f,
		  1.0f, -1.0f, -1.0f,
		  1.0f, -1.0f,  1.0f,

		  1.0f, -1.0f,  1.0f,
		 -1.0f, -1.0f,  1.0f,
		 -1.0f, -1.0f, -1.0f,
	};

	const float TRIANGLE_CUBE_UVS[] = {
		0, 0,
		1, 0,
		1, 1,

		1, 1,
		0, 1,
		0, 0,

		0, 0,
		0, 1,
		1, 1,

		1, 1,
		1, 0,
		0, 0,

		0, 0,
		1, 0,
		1, 1,

		1, 1,
		0, 1,
		0, 0,

		0, 0,
		0, 1,
		1, 1,

		1, 1,
		1, 0,
		0, 0,

		0, 0,
		0, 1,
		1, 1,

		1, 1,
		1, 0,
		0, 0,


		0, 0,
		0, 1,
		1, 1,

		1, 1,
		1, 0,
		0, 0
	};

	const float TRIANGLE_PYRAMID_VERTS[] = {
		//bottom face
		 -1.0f, -1.0f, -1.0f,
		  1.0f, -1.0f, -1.0f,
		  1.0f, -1.0f,  1.0f,

		  1.0f, -1.0f,  1.0f,
		 -1.0f, -1.0f,  1.0f,
		 -1.0f, -1.0f, -1.0f,

		 //left wall
		 -1.0f, -1.0f, -1.0f,
		 -1.0f, -1.0f,  1.0f,
		  0.0f,  1.0f,  0.0f,

		//right wall
		  1.0f,  -1.0f,  -1.0f,
		  0.0f,   1.0f,   0.0f,
		  1.0f,  -1.0f,   1.0f,

		//front wall
		  1.0f,   -1.0f,   1.0f,
		  0.0f,    1.0f,   0.0f,
		 -1.0f,   -1.0f,   1.0f,

		//back wall
		 -1.0f, -1.0f, -1.0f, 
		  0.0f,  1.0f,  0.0f, 
		  1.0f, -1.0f, -1.0f, 
	};

	const float TRIANGLE_PYRAMID_UVS[] = {
		0, 0,
		0, 1,
		1, 1,

		1, 1,
		1, 0,
		0, 0,

		0, 0,
		0.5f, 1,
		1, 0,

		0, 0,
		0.5f, 1,
		1, 0,

		0, 0,
		0.5f, 1,
		1, 0,

		0, 0,
		0.5f, 1,
		1, 0,
	};
}

// Specify how many vertices we need to draw one polygon of this shape
enum class DrawMode {
	TRIANGLES = 3,
	QUAD = 4
};

#endif