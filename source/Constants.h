#ifndef CONSTANTS_H
#define CONSTANTS_H

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

	const float PYRAMID_VERTS[] = {
		//base
		-0.5f, -0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f,
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
}

#endif