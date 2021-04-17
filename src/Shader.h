#pragma once

#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdint.h>

class Shader {
public: 
	// constructor reads and builds the shader
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();
	// use/activate the shader
	void use() const;
	// utility uniform functions
	template <typename T> void setUniform(const std::string& name, T value) const;

	uint32_t getRendererID();

private:
	// the program reference ID
	uint32_t rendererID;
	uint32_t compileFragmentShader(const char* fragmentShaderSource);
	uint32_t compileVertexShader(const char* vertexShaderSource);
	uint32_t linkShaders(uint32_t vertexShader, uint32_t fragmentShader);
	bool assertCompilation(uint32_t shader);
	bool assertLinking(uint32_t shaderProgram);

};

