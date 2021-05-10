#pragma once

#include <string>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

/**
 * Handles the window states and buffers
 */
class Window
{
public:
	Window();
	~Window();
	int32_t windowClosing();
	GLFWwindow* getGlfwWindow() const;
	void swapBuffers();
	void pollEvents();

private:
	GLFWwindow* m_glfwWindow;

	static constexpr uint8_t majorVer = 3;
	static constexpr uint8_t minorVer = 3;
	static constexpr uint32_t height = 600;
	static constexpr uint32_t width = 800;
	static constexpr std::string_view windowName = "Island Game";
};

