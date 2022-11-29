#ifndef CAMERA_H
#define CAMERA_H
#include <nds.h>
#include "ADT/Transform.h"
#include "Input/Input.h"

// C++ is a lawless land. I chose to put implementation details in the header this time because I am a lawless person.

class Camera {
private:
	float yaw;
	Vector3f camFront;  // The actual direction our camera is looking at
	Vector3f position;  // Our camera's position in the world
	float camVelocity = 0.05f;
public:
	Camera() {
		yaw = -90;
		position.z = 5.0f;
	}

	void updateInput() {
		if (Input::getButton("left"))
			yaw -= 2.0f;
		if (Input::getButton("right"))
			yaw += 2.0f;
		if (Input::getButton("forward"))
			position = position - camFront * camVelocity;
		if (Input::getButton("backward"))
			position = position + camFront * camVelocity;
	}

	void updateCamera() {
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		Vector3f direction;  // Store where our camera is looking using euler angles (but not normalized)
		s16 xCompYaw = cosLerp((yaw / 360) * 32767);  // Transform from degrees to 32767
		s16 zCompYaw = sinLerp((yaw / 360) * 32767);
		direction.x = fixedToFloat(xCompYaw, 12);
		direction.z = fixedToFloat(zCompYaw, 12);
		camFront = Vector3f::normalize(direction);  // Now we normalize it so the speed doesn't change on magnitude.
		Vector3f target = position + camFront;

		// Look at takes care of the rest for us, takes a camera position, a target position, and an up vector (just y axis).
		gluLookAt(position.x, position.y, position.z, target.x, target.y, target.z, 0, 1, 0);
	}
};

#endif