#pragma once
#include <vector>

#include "Window.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

class KeyInput
{
public:
	KeyInput(GLFWwindow* window);
	~KeyInput();
	bool isPressed(int32_t pressedKey);

private:
	GLFWwindow* linkedWindow;
};

