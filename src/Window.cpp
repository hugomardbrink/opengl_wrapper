#include "Window.h"

/**
 * Called everytime window is resized
 * @note Should be part of class
 */
void framebuffer_size_callback(GLFWwindow* glfwWindow, int32_t width, int32_t height) {
	glViewport(0, 0, width, height);
}


Window::Window()
{
	// Core-profile, ver 3.3
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVer);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVer);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create window object
	glfwWindow = glfwCreateWindow(width, height, std::string(windowName).c_str(), NULL, NULL);

	if (!glfwWindow)
	{
		std::cout << "ERROR::WINDOW::CREATION_FAILED" << std::endl;
		glfwTerminate();
	}

	// Create window on calling thread
	glfwMakeContextCurrent(glfwWindow);


	// Exit if wrong OS
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "ERROR::GLAD::INITIALIZATION_FAILED" << std::endl;
		glfwTerminate();
	}

	// Tells openGL the rendering dimensions, (0,0) is bottom left
	glViewport(0, 0, width, height);

	// Use function when window is resized
	glfwSetFramebufferSizeCallback(glfwWindow, framebuffer_size_callback);
}


Window::~Window()
{
	glfwTerminate();
}

int32_t Window::windowClosing() {
	return glfwWindowShouldClose(glfwWindow);
}

GLFWwindow* Window::getGlfwWindow()
{
	return glfwWindow;
}

void Window::swapBuffers()
{
	glfwSwapBuffers(glfwWindow);
}

void Window::pollEvents()
{
	glfwPollEvents();
}

