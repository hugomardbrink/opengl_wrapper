#include "Input.h"

bool Input::isKeyPressed(void* targetWindow, uint32_t keyCode)
{
	return glfwGetKey(static_cast<GLFWwindow*>(targetWindow), keyCode);
}

bool Input::isMouseButtonPressed(void* targetWindow, uint32_t buttonCode)
{
	return glfwGetMouseButton(static_cast<GLFWwindow*>(targetWindow), buttonCode) == GLFW_PRESS;
}

glm::vec2 Input::getMousePosition(void* targetWindow)
{

}

void Input::enableCursor(void* targetWindow)
{
	glfwSetInputMode(static_cast<GLFWwindow*>(targetWindow), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Input::disableCursor(void* targetWindow)
{
	glfwSetInputMode(static_cast<GLFWwindow*>(targetWindow), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}
