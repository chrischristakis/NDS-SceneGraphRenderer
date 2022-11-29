#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H
#include "Component.h"
#include "../ADT/Transform.h"
#include <map>

class AnimationComponent : public Component {
	// Key: 'timestamp', the frame to render it on, Value: desired transform keyframe
	std::map<int, Transform*> animations;  
	int currentFrame, targetFrame, frameCounter;

	int getNextTargetFrame();
public:
	Transform animatedTransform;  // The fruit of our labours, use this to ainimate the resulting transform.

	AnimationComponent();
	~AnimationComponent();
	void addKeyframe(int keyframe, Transform* transform);
	void update();

};

#endif