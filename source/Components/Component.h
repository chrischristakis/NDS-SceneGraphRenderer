#ifndef COMPONENT_H
#define COMPONENT_H
//! NOTE: It's important that when a class derives from Component, it does so PUBLICLY!
//! We need to do this so we can use the static_cast operator in the GameObject class.

// Very bare bones. The whole point of this is basically for readability and a way to store generic class pointers
// in our gameobject's components list.

// I also am aware that in most entity component systems, by the books you shouldn't have logic in a component, only data.
// But I kinda wanna try a hybrid model here to experiment where components have logic. Might be spaghetti, but we'll see.
struct Component {
	Component() = default;
	virtual ~Component() {};
};

#endif