#pragma once
#include <stdint.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


/**
 * Handles input from keyboard and mouse
 */
class Input
{
public: 
	bool isKeyPressed(void* targetWindow, uint32_t keyCode);
	bool isMouseButtonPressed(void* targetWindow, uint32_t buttonCode);
	glm::vec2 getMousePosition(void* targetWindow);

	void enableCursor(void* targetWindow);
	void disableCursor(void* targetWindow);

private:


};

