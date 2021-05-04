#include "KeyInput.h"

KeyInput::KeyInput(GLFWwindow* window) : 
linkedWindow(window){}

KeyInput::~KeyInput()
{

}

bool KeyInput::isPressed(int32_t pressedKey)
{
	return glfwGetKey(linkedWindow, pressedKey) == GLFW_PRESS;
}
