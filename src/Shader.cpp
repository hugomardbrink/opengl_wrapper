#include "Shader.h"


/**
 * Compiles fragment and vertex shaders and allocates GPU-resource for a shader program
 * @param vertexPath The system-path to the vertex shader
 * @param fragmentPath The system-path to the fragment shader
 */
Shader::Shader(const char* vertexPath, const char* fragmentPath) 
{
	// Stores files for shaders
	std::ifstream vertexFile, fragmentFile;

	std::string vertexSourceCode,fragmentSourceCode;

	std::stringstream vertexStream, fragmentStream;

	// Ensure ifstream objects can throw exceptions:
	vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try 
	{
		vertexFile.open(vertexPath);
		fragmentFile.open(fragmentPath);

		// Read files content into stream
		vertexStream << vertexFile.rdbuf();
		fragmentStream << fragmentFile.rdbuf();

		vertexFile.close();
		fragmentFile.close();

		// Convert stream content to strings
		vertexSourceCode = vertexStream.str();
		fragmentSourceCode = fragmentStream.str();
	} 
	catch(std::ifstream::failure e) 
	{
		std::cout << "ERROR::SHADER::FILE_FAILED_TO_READ\n" << std::endl;
	}

	uint32_t vertexShaderID = compileVertexShader(vertexSourceCode.c_str());
	uint32_t fragmentShaderID = compileFragmentShader(fragmentSourceCode.c_str());
	linkShaders(vertexShaderID, fragmentShaderID);

	// Deallocates GPU-resource 
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
}

/**
 * Deallocates the GPU-resource for the shader program
 */
Shader::~Shader() 
{
	glDeleteProgram(m_rendererID);
}

/**
 * Compiles the fragment shader
 * @param fragmentSourceCode The source code for the fragment shader
 * @return ID for fragment shader
 */
uint32_t Shader::compileFragmentShader(const char* fragmentSourceCode)
{
	uint32_t fragmentShaderID;
	fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Adds source code to created shader and compiles it
	glShaderSource(fragmentShaderID, 1, &fragmentSourceCode, NULL);
	glCompileShader(fragmentShaderID);

	logCompilationStatus(fragmentShaderID);

	return fragmentShaderID;
}

/**
 * Compiles the vertex shader
 * @param vertexSourceCode The source code for the vertex shader
 * @return ID for the vertex shader
 */
uint32_t Shader::compileVertexShader(const char* vertexSourceCode)
{
	uint32_t vertexShaderID;
	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);

	// Adds source code to created shader and compiles it
	glShaderSource(vertexShaderID, 1, &vertexSourceCode, NULL);
	glCompileShader(vertexShaderID);

	logCompilationStatus(vertexShaderID);

	return vertexShaderID;
}

/**
 * Set this shader as active shader in opengl
 */
void Shader::use() const
{
	glUseProgram(m_rendererID);
}

/**
 * Asserts if compilation of shaders was successful
 * @param shader The shader ID to validate compilation
 */
void Shader::logCompilationStatus(uint32_t shaderID) 
{
	int32_t success;
	char infoLog[512];
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);  // Check if shader compilation failed, result is stored in var

	if (!success) {  // If compilation failed, use glGetShaderInfoLog() to retrieve fail status, then output it to console.
		glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	else std::cout << "Shader " << shaderID << " compiled successfully..." << std::endl;
}

/**
 * Asserts if linking of shaders was successful
 */
void Shader::logLinkingStatus() 
{
	int32_t success;
	char infoLog[512];

	glGetProgramiv(m_rendererID, GL_LINK_STATUS, &success);

	if (!success)
	{ 
		glGetShaderInfoLog(m_rendererID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED" << infoLog << std::endl;
	}
	else std::cout << "Shaders linked successfully..." << std::endl;
}


/**
 * Links vertex and fragment shader to a shader program
 * @param vertexShaderID The reference ID for the vertex shader
 * @param fragmentShaderID The reference ID for the fragment shader
 */
void Shader::linkShaders(uint32_t vertexShaderID, uint32_t fragmentShaderID) 
{
	// Allocates GPU-Resource for shader
	m_rendererID = glCreateProgram();

	// Attach vertex and fragment shaders
	glAttachShader(m_rendererID, vertexShaderID);
	glAttachShader(m_rendererID, fragmentShaderID);

	// Links attached shaders to program
	glLinkProgram(m_rendererID);
	logLinkingStatus();

	// Free up GPU-Resource
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
}

/**
 * Catch all types not supported and throws error, should never be used
 * @param name The name of the uniform var in the shader
 * @param value The value assigned to the uniform
 */
template <typename T> void Shader::setUniform(const std::string& name, T value) const
{
	std::cout << "ERROR::SHADER::UNIFORM_TYPE_NOT_SUPPORTED" << std::endl;
	static_assert(false);
}

/**
 * Sets uniform for bool uniforms
 * @param name The name of the uniform var in the shader
 * @param value The value assigned to the uniform
 */
template <> void Shader::setUniform<bool>(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(m_rendererID, name.c_str()), value);
}

/**
 * Sets uniform for integer uniforms
 * @param name The name of the uniform var in the shader
 * @param value The value assigned to the uniform
 */
template <> void Shader::setUniform<int>(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(m_rendererID, name.c_str()), value);
}

/**
 * Sets uniform for float uniforms
 * @param name The name of the uniform var in the shader
 * @param value The value assigned to the uniform
 */
template <> void Shader::setUniform<float>(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(m_rendererID, name.c_str()), value);
}

/**
 * Sets uniform for 4x4 matrix uniforms
 * @param name The name of the uniform var in the shader
 * @param value The value assigned to the uniform
 */
template <> void Shader::setUniform<glm::mat4>(const std::string& name, glm::mat4 value) const
{
	glUniformMatrix4fv(glGetUniformLocation(m_rendererID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

/**
 * @return the opengl reference ID
 */
uint32_t Shader::getRendererID() 
{
	return m_rendererID;
}