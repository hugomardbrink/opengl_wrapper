#pragma once
#include <vector>

#include "Window.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

class KeyInput
{
public:
	KeyInput(GLFWwindow* linkedWindow);
	~KeyInput();
	bool isPressed(int32_t key);

private:
	GLFWwindow* m_linkedWindow;
};

