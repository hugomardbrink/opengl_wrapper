#pragma once
#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "VertexArray.h"
#include "Shader.h"
#include "ElementBuffer.h"


/**
 * Handles rendering in the window
 */
class Renderer
{
public:
	void clear(glm::vec4 colour) const;
	void draw(const VertexArray& VAO, const ElementBuffer& EBO, const Shader& shader) const;
};

