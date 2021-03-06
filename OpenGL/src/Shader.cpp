#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
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

Shader::~Shader()
{
	GLCall(glDeleteProgram(m_RendererID));
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

	m_RendererID = glCreateProgram();
	unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertexPath);
	unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentPath);
	// Attach shaders to our program
	glAttachShader(m_RendererID, vertexShader);
	glAttachShader(m_RendererID, fragmentShader);
	// Link shaders 
	glLinkProgram(m_RendererID);
	// Validate and check for errors
	glValidateProgram(m_RendererID);

	glGetProgramiv(m_RendererID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(m_RendererID, sizeof(msg), nullptr, msg);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING::FAILED!\n" << msg << std::endl;
	}
	
	// Delete shaders since we don't need them, because they're already linked into program
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return m_RendererID;
}

void Shader::Bind() const
{
	GLCall(glUseProgram(m_RendererID));
}

void Shader::Unbind() const
{
	GLCall(glUseProgram(0));
}

void Shader::SetUniform4f(const std::string& name, float v1, float v2, float v3, float va)
{
	GLCall(glUniform4f(GetUniformLocation(name), v1, v2, v3, va));
}

unsigned int Shader::GetUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
	{
		return m_UniformLocationCache[name];
	}
	else
	{
		GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
		if (location == -1)
		{
			std::cout << "[WARNING] - Uniform " << name << " has not been found!" << std::endl;
		}
		else
		{
			m_UniformLocationCache[name] = location;
			return location;
		}
	}

}