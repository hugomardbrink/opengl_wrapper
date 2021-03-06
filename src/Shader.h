#pragma once

#include <glad/glad.h> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdint.h>


/**
 * Handles a shader program. Supports vertex and fragment shaders
 */
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
	uint32_t m_rendererID;
	uint32_t compileFragmentShader(const char* fragmentShaderSource);
	uint32_t compileVertexShader(const char* vertexShaderSource);
	void linkShaders(uint32_t vertexShaderID, uint32_t fragmentShaderID);
	void logCompilationStatus(uint32_t shaderID);
	void logLinkingStatus();

};

