#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <map>
#include <string>
#include <utility>
#include <typeinfo>
#include "../Components/Component.h"

class GameObject {
public: 
	
	GameObject() = default;

	std::map<std::string, Component*> components;

	// Add a component (Note: You can only have one of each type of component in a GameObject)
	template<typename T, typename ...TArgs>
	void addComponent(TArgs&&... args) {
		// Create a template pointer for our component
		T* component(new T(std::forward<TArgs>(args)...));

		//The name of our class (Typeid is implementation dependant, only using it as a key though so doesn't matter)
		std::string typeName{ typeid(T).name() };

		// We insert into our list of components after casting our template pointer to a component pointer.
		// .insert() ignores the insertion if a key already exists, hence the one component rule.
		components.insert({ typeName, static_cast<Component*>(component) });
	}

	// Get a component given its class type. We only have one of these types in the components map, so this works.
	template<class T>
	T* getComponent() {
		std::string typeName{ typeid(T).name() };

		// If the component doesn't exist, just return a null component pointer.
		if (components.find(typeName) == components.end())
			return static_cast<T*>(nullptr);

		return static_cast<T*>(components[typeName]);
	}

	// Remove a component from our components list given the type.
	template<class T>
	void removeComponent() {
		std::string typeName = typeid(T).name();
		std::map<std::string, Component*>::iterator it = components.find(typeName);

		if (it == components.end())  // If it doesn't exist in the map we don't have to do anything.
			return;
		Component* component = it->second;  //Second gives us the component pointer, first would be the className.
		components.erase(it);
		delete component;  // It's important we dealocate memory once it's gone from the map.
	}


};

#endif