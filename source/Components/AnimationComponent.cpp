#include "AnimationComponent.h"
#include <limits>
#include <algorithm>
#include <stdio.h>

// The first keyframe should be the object's transform itself.
AnimationComponent::AnimationComponent() {
	addKeyframe(0, new Transform());
	frameCounter = 0;
	currentFrame = 0;
	targetFrame = std::numeric_limits<int>::max(); // No target frame yet, so set to biggest int.
}

AnimationComponent::~AnimationComponent() {
	for (auto it = animations.begin(); it != animations.end(); it++)
		delete it->second;
	animations.clear();
}

void AnimationComponent::addKeyframe(int keyframe, Transform* transform) {
	animations.insert({ keyframe, transform });

	// If the new keyframe falls between our current frame and current target frame,
	// use it next instead of the old target frame.
	if (keyframe < targetFrame && keyframe > currentFrame)
		targetFrame = keyframe;
}

// Get the next frame we must animate in our animation, based on our current Target frame.
int AnimationComponent::getNextTargetFrame() {
	for (auto it = animations.begin(); it != animations.end(); it++)
		if (it->first > targetFrame)
			return it->first;
	return 0;  // Default to first keyframe if we dont find another frame greater than current target frame.
}

void AnimationComponent::update() {
	// If there's 0 frames, we don't really have an animation, so skip.
	if (animations.size() < 1) return;

	//Now let us calculate our current transform in the animation based off the two keyframes we're inbetween.
	// DeltaTransform holds the difference between our two frames.
	Transform &currentTransform = *animations[currentFrame];
	Transform &targetTransform = *animations[targetFrame];
	Transform deltaTransform;

	// How we interpolate between frames, just calculate the distance between two frames and multipy by the progress to the next frame.
	float lerp = frameCounter / static_cast<float>(targetFrame - currentFrame); // value from [0-1]

	deltaTransform.translate = (targetTransform.translate - currentTransform.translate) * lerp;
	deltaTransform.scale = (targetTransform.scale - currentTransform.scale) * lerp;
	deltaTransform.angle = (targetTransform.angle - currentTransform.angle) * lerp;
	deltaTransform.angleAxis = (targetTransform.angleAxis - currentTransform.angleAxis) * lerp;

	// We must add the progress of our lerped animation to the previous keyframe, which will bring us to our target keyframe.
	animatedTransform.translate = currentTransform.translate + deltaTransform.translate;
	animatedTransform.scale = currentTransform.scale + deltaTransform.scale;
	animatedTransform.angle = currentTransform.angle + deltaTransform.angle;
	animatedTransform.angleAxis = currentTransform.angleAxis + deltaTransform.angleAxis;

	// Once we're done lerping, we have to reset onto the next frame.
	if (++frameCounter > targetFrame - currentFrame) {
		frameCounter = 0;
		currentFrame = targetFrame;

		// Used when we hit the end of an animation, reset everything.
		targetFrame = getNextTargetFrame();
		if (targetFrame == 0) {
			currentFrame = 0;
			targetFrame = getNextTargetFrame();
		}
	}
}