#pragma once

#include "StdAfx.h"
#include <unordered_map>

class Shader
{
private:
	unsigned int m_RendererID; // Shader program ID
	std::unordered_map<std::string, int> m_UniformLocationCache;
public:
	// Constructor - reads and builds shader
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();

	// Use / Activate shader
	void Bind() const;
	void Unbind() const;

	// Uniform functions
	void SetUniform4f(const std::string& name, float v1, float v2, float v3, float va); // RGBA

private:
	// Create shaders
	unsigned int CreateShader(const std::string& vertexPath, const std::string& fragmentPath);
	// Compile shader
	unsigned int CompileShader(unsigned int type, const std::string& src);
	// Retrieve uniform location
	unsigned int GetUniformLocation(const std::string& name);

};