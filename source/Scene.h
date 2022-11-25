#ifndef SCENE_H
#define SCENE_H

struct Scene {
	GameObject root;
	Scene(); //Initialize here
	void render() {  // Our ECS system is baked into the scene class
		updateMV(); using components
	}

	addChild(GameObject go); //Return id
};

#endif