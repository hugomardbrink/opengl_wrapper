#include "MouseInput.h"

MouseInput::MouseInput(GLFWwindow* window, glm::vec2 startPosition) :
	linkedWindow(window),
	position(startPosition) {}

MouseInput::~MouseInput()
{

}

void MouseInput::enableCursor()
{
	glfwSetInputMode(linkedWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void MouseInput::disableCursor()
{
	glfwSetInputMode(linkedWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

glm::vec2 MouseInput::getPosition()
{
	return position;
}
