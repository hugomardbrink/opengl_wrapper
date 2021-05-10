#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



class MouseInput
{
public:
	MouseInput(GLFWwindow* linkedWindow, glm::vec2 position);
	~MouseInput();
	void enableCursor();
	void disableCursor();
	glm::vec2 getPosition();
private:
	GLFWwindow* m_linkedWindow;
	glm::vec2 m_position;
};

