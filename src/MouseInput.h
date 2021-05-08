#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



class MouseInput
{
public:
	MouseInput(GLFWwindow* window, glm::vec2 startPosition);
	~MouseInput();
	void enableCursor();
	void disableCursor();
	glm::vec2 getPosition();
private:
	GLFWwindow* linkedWindow;
	glm::vec2 position;
};

