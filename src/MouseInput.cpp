#include "MouseInput.h"

MouseInput::MouseInput(GLFWwindow* linkedWindow, glm::vec2 position) :
	m_linkedWindow(linkedWindow),
	m_position(position) {}

MouseInput::~MouseInput()
{

}

void MouseInput::enableCursor()
{
	glfwSetInputMode(m_linkedWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void MouseInput::disableCursor()
{
	glfwSetInputMode(m_linkedWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

glm::vec2 MouseInput::getPosition()
{
	return m_position;
}
