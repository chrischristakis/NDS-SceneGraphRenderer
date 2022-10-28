#include "Transform.h"

void Transform::setAngle(float angle, float x, float y, float z) {
	this->angle = angle;
	angleAxis.x = x;
	angleAxis.y = y;
	angleAxis.z = z;
}

void Transform::setTranslate(float x, float y, float z) {
	translate.x = x;
	translate.y = y;
	translate.z = z;
}

void Transform::deltaTranslate(float dx, float dy, float dz) {
	translate.x += dx;
	translate.y += dy;
	translate.z += dz;
}

void Transform::setScale(float x, float y, float z) {
	scale.x = x;
	scale.y = y;
	scale.z = z;
}