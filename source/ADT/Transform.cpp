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

void Transform::setScale(float x, float y, float z) {
	scale.x = x;
	scale.y = y;
	scale.z = z;
}