#include "Input.h"

std::map<std::string, KEYPAD_BITS> Input::keyMapping;

// Assign all virtual input names.
void Input::init() {
	keyMapping["jump"] = KEYPAD_BITS::KEY_A;
	keyMapping["fire"] = KEYPAD_BITS::KEY_B;
	keyMapping["left"] = KEYPAD_BITS::KEY_LEFT;
	keyMapping["right"] = KEYPAD_BITS::KEY_RIGHT;
	keyMapping["up"] = KEYPAD_BITS::KEY_UP;
	keyMapping["down"] = KEYPAD_BITS::KEY_DOWN;
	keyMapping["start"] = KEYPAD_BITS::KEY_START;
}

bool Input::getButton(std::string buttonName) {
	int keys = keysHeld();
	return keys & keyMapping[buttonName];
}

// Since we don't have a UI, if you want to assign "jump" to B, use this.
void Input::assignButton(std::string buttonName, KEYPAD_BITS newButton) {
	// Just end it if the virtual input doesn't exist.
	if (keyMapping.find(buttonName) == keyMapping.end())
		return; 

	keyMapping[buttonName] = newButton;
}

// This allows us to change a virtual input name. 
// So for example, "fire" can be changed to "interact" through swapButtonName("fire", "interact")
void Input::swapButtonName(std::string oldName, std::string newName) {
	std::map<std::string, KEYPAD_BITS>::iterator it = keyMapping.find(oldName);

	if (it == keyMapping.end())  // Key not found, cant modify it 
		return;

	KEYPAD_BITS val = keyMapping[oldName];

	keyMapping[newName] = val;

	keyMapping.erase(it);  // remove old key
}