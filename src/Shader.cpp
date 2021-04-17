#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath) 
{
	// Stores files for shaders
	std::ifstream vertexFile;
	std::ifstream fragmentFile;

	// Stores source code of the shaders
	std::string vertexSourceCode;
	std::string fragmentSourceCode;

	// ensure ifstream objects can throw exceptions:
	vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try 
	{
		// Open shader files
		vertexFile.open(vertexPath);
		fragmentFile.open(fragmentPath);

		// Stores streams from shader files
		std::stringstream vertexStream, fragmentStream;

		// Read files content into stream
		vertexStream << vertexFile.rdbuf();
		fragmentStream << fragmentFile.rdbuf();

		// Close files
		vertexFile.close();
		fragmentFile.close();

		// Convert stream content to strings
		vertexSourceCode = vertexStream.str();
		fragmentSourceCode = fragmentStream.str();
	} 
	catch(std::ifstream::failure e) 
	{
		std::cout << "ERROR::SHADER::FILE_FAILED_TO_READ" << std::endl;
	}

	uint32_t vertexShader = compileVertexShader(vertexSourceCode.c_str());
	uint32_t fragmentShader = compileFragmentShader(fragmentSourceCode.c_str());
	rendererID = linkShaders(vertexShader, fragmentShader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader() 
{
	glDeleteProgram(rendererID);
}

uint32_t Shader::compileFragmentShader(const char* fragmentSourceCode)
{
	// Creates a ID reference to a fragment shader
	uint32_t fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Compiles the fragmentshader with same standard as above
	glShaderSource(fragmentShader, 1, &fragmentSourceCode, NULL);
	glCompileShader(fragmentShader);


	if (!(assertCompilation(fragmentShader)))
		return 0;

	return fragmentShader;
}

uint32_t Shader::compileVertexShader(const char* vertexSourceCode)
{
	uint32_t vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER); // Create a shader referenced by this ID. 

	// Takes the ID shader reference, 1 string of source code, the source code of the shader, 4th is ignored
	// With these parameters it generates source code for the shader
	glShaderSource(vertexShader, 1, &vertexSourceCode, NULL);
	glCompileShader(vertexShader);  // Compiles the shader's source code

	if (!(assertCompilation(vertexShader)))
		return 0;

	return vertexShader;
}

void Shader::use() const
{
	glUseProgram(rendererID);
}

bool Shader::assertCompilation(uint32_t shader) 
{
	int32_t success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);  // Check if shader compilation failed, result is stored in var

	if (!success) {  // If compilation failed, use glGetShaderInfoLog() to retrieve fail status, then output it to console.
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		return 0;
	}

	return 1;
}

bool Shader::assertLinking(uint32_t shaderProgram) 
{
	int32_t success;
	char infoLog[512];

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if (!success) {  // If compilation failed, use glGetShaderInfoLog() to retrieve fail status, then output it to console.
		glGetShaderInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		return 0;
	}

	return 1;
}

uint32_t Shader::linkShaders(uint32_t vertexShader, uint32_t fragmentShader) 
{

	// When vertex and fragment shader is created we the to link them to shader program object which will be called when rendering
	// Linking links vertex into next shader and frament into next etc...
	// Input and outputs must match
	uint32_t shaderProgram;
	shaderProgram = glCreateProgram();  //Create a reference ID to a program object

	// Attach our vertex and Fragment shader to the program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// Link all shaders to the program object
	glLinkProgram(shaderProgram);

	if (!(assertLinking(shaderProgram)))
		return 0;

	// Delete shader object after linking is done
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}

template <typename T> void Shader::setUniform(const std::string& name, T value) const
{
	std::cout << "ERROR::SHADER::UNIFORM_TYPE_NOT_SUPPORTED" << std::endl;
	static_assert(false);
}

template <> void Shader::setUniform<bool>(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(rendererID, name.c_str()), value);
}

template <> void Shader::setUniform<int>(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(rendererID, name.c_str()), value);
}

template <> void Shader::setUniform<float>(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(rendererID, name.c_str()), value);
}

template <> void Shader::setUniform<glm::mat4>(const std::string& name, glm::mat4 value) const
{
	glUniformMatrix4fv(glGetUniformLocation(rendererID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

uint32_t Shader::getRendererID() 
{
	return rendererID;
}