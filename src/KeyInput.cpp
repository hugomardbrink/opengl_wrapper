#include "KeyInput.h"

KeyInput::KeyInput(GLFWwindow* linkedWindow) : 
m_linkedWindow(linkedWindow){}

KeyInput::~KeyInput()
{

}

bool KeyInput::isPressed(int32_t key)
{
	return glfwGetKey(m_linkedWindow, key);
}