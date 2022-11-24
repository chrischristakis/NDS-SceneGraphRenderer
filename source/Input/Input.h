#ifndef INPUT_H
#define INPUT_H
#include <string>
#include <map>
#include <nds.h>

class Input {
public:
	static void init();
	static bool getButton(std::string buttonName);
	static void swapButtonName(std::string oldName, std::string newName);
	static void assignButton(std::string buttonName, KEYPAD_BITS newButton);
private: 
	Input() {};
	static std::map<std::string, KEYPAD_BITS> keyMapping;
};

#endif