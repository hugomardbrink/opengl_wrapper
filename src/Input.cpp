#include "Input.h"

/**
 * Checks if key is pressed
 * @param targetWindow The window to check press
 * @param keyCode the GLFW code for the keyboard key
 * @return if the key is pressed or not
 */
bool Input::isKeyPressed(void* targetWindow, uint32_t keyCode)
{
	return glfwGetKey(static_cast<GLFWwindow*>(targetWindow), keyCode);
}

/**
 * Check if mouse button is pressed
 * @param targetWindow The window to check the press
 * @param buttonCode the GLFW code for the mouse button
 * @return if the key is pressed or not
 */
bool Input::isMouseButtonPressed(void* targetWindow, uint32_t buttonCode)
{
	return glfwGetMouseButton(static_cast<GLFWwindow*>(targetWindow), buttonCode) == GLFW_PRESS;
}

/**
 * Gets the cursor position in a window
 * @param targetWindow The window to check the position
 * @return A 2D vector with x and y position
 */
glm::vec2 Input::getMousePosition(void* targetWindow)
{
	double x, y;
	glfwGetCursorPos(static_cast<GLFWwindow*>(targetWindow), &x, &y);

	return glm::vec2((float)x, (float)y);
}

/**
 * Enables cursor in window
 * @param targetWindow The window to enable the cursor in
 */
void Input::enableCursor(void* targetWindow)
{
	glfwSetInputMode(static_cast<GLFWwindow*>(targetWindow), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

/**
 * Disables cursor in window
 * @param targetWindow The window to disable the cursor in
 */
void Input::disableCursor(void* targetWindow)
{
	glfwSetInputMode(static_cast<GLFWwindow*>(targetWindow), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}
