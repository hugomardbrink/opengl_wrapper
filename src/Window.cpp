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

/**
 * Deallocate glfw resources
 */
Window::~Window()
{
	glfwTerminate();
}

/**
 * @return 1 if window is closing, 0 if not
 */
int32_t Window::windowClosing() {
	return glfwWindowShouldClose(glfwWindow);
}

/**
 * @return pointer to glfw window
 */
GLFWwindow* Window::getGlfwWindow()
{
	return glfwWindow;
}

/**
 * Swaps pixels with 2D colour buffer
 */
void Window::swapBuffers()
{
	glfwSwapBuffers(glfwWindow);
}

/**
 * Triggers events
 */
void Window::pollEvents()
{
	glfwPollEvents();
}

/**
 * Processes inputs from the keyboard
 * @note should be event triggers
 * @note could be in wrong location
 */
void Window::processInput()
{
    // Checks if escape key is pressed, then closes window
    if (glfwGetKey(glfwWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)  
        glfwSetWindowShouldClose(glfwWindow, true);

    if (glfwGetKey(glfwWindow, GLFW_KEY_W) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    if (glfwGetKey(glfwWindow, GLFW_KEY_Q) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

