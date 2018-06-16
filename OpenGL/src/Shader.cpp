#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	m_ID = 0;

	// Retrieve Vertex/Fragment shader source code from it's file
	std::string vertexShaderSource;
	std::string fragmentShaderSource;

	std::ifstream vertexFile;
	std::ifstream fragmentFile;
	// Set exceptions
	vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try 
	{
		// Open files
		vertexFile.open(vertexPath);
		fragmentFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		// Push contents into stream
		vShaderStream << vertexFile.rdbuf();
		fShaderStream << fragmentFile.rdbuf();
		// Close files
		vertexFile.close();
		fragmentFile.close();
		// Convert streams into string
		vertexShaderSource = vShaderStream.str();
		fragmentShaderSource = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cerr << "ERROR::SHADER::FAILED_TO_READ_FILE!" << std::endl;
	}

	CreateShader(vertexShaderSource, fragmentShaderSource);
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& src)
{
	int success;
	char msg[1024];

	unsigned int id = glCreateShader(type);
	const char* shaderSource = src.c_str();
	glShaderSource(id, 1, &shaderSource, nullptr);
	glCompileShader(id);

	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(id, sizeof(msg), nullptr, msg);
		std::cout << "ERROR::" << (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT") << "::SHADER::COMPILATION::FAILED!\n" << msg << std::endl;
		glDeleteShader(id);
		return -1;
	}

	return id;
}

unsigned int Shader::CreateShader(const std::string& vertexPath, const std::string& fragmentPath)
{
	int success;
	char msg[1024];

	m_ID = glCreateProgram();
	unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertexPath);
	unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentPath);
	// Attach shaders to our program
	glAttachShader(m_ID, vertexShader);
	glAttachShader(m_ID, fragmentShader);
	// Link shaders 
	glLinkProgram(m_ID);
	// Validate and check for errors
	glValidateProgram(m_ID);

	glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(m_ID, sizeof(msg), nullptr, msg);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING::FAILED!\n" << msg << std::endl;
	}
	
	// Delete shaders since we don't need them, because they're already linked into our program
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return m_ID;
}

void Shader::Use()
{
	glUseProgram(m_ID);
}

void Shader::Delete()
{
	glDeleteProgram(m_ID);
}

void Shader::SetFloat(const std::string& name, float v1, float v2, float v3, float va) const
{
	glUniform4f(glGetUniformLocation(m_ID, name.c_str()), v1, v2, v3, va);
}