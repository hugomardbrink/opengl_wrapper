#pragma once
#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include <GLFW/glfw3.h>
#include "VertexArray.h"
#include "Shader.h"
#include "ElementBuffer.h"


class Renderer
{
public:
	void clear() const;
	void draw(const VertexArray& VAO, const ElementBuffer& EBO, const Shader& shader) const;
};

