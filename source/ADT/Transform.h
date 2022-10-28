#ifndef TRANSFORM_H
#define TRANSFORM_H

struct Vector3f {
	float x, y, z;
	Vector3f(float x, float y, float z): x(x), y(y), z(z) {}
	Vector3f(): x(0), y(0), z(0) {}
};

struct Transform {
	Vector3f scale = Vector3f(1.0f, 1.0f, 1.0f);
	Vector3f translate;
	Vector3f angleAxis;
	float angle = 0;

	void setScale(float x, float y, float z);
	void setTranslate(float x, float y, float z);
	void deltaTranslate(float dx, float dy, float dz);
	void setAngle(float angle, float x, float y, float z);
};

#endif