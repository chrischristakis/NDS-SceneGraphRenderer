#include "Transform.h"
#include <cmath>

Vector3f operator+(const Vector3f lhs, const Vector3f rhs) {
	return Vector3f(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

Vector3f operator-(const Vector3f lhs, const Vector3f rhs) {
	return Vector3f(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

Vector3f operator*(const Vector3f lhs, const Vector3f rhs) {
	return Vector3f(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
}

Vector3f operator*(const Vector3f lhs, const float scalar) {
	return Vector3f(lhs.x * scalar, lhs.y * scalar, lhs.z * scalar);
}

Vector3f Vector3f::normalize(const Vector3f vec) {
	double mag = std::sqrt(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z);
	Vector3f res(vec.x / mag, vec.y / mag, vec.z / mag);
	return res;
}

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