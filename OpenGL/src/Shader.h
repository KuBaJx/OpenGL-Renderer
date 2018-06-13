#pragma once

#include "StdAfx.h"

class Shader
{
public:
	unsigned int m_ID; // Program

	// Constructor - reads and builds shader
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

	// Use / Activate shader
	void Use();
	// Uniform function
	void SetBool(const std::string& name, bool value) const;
	void SetInt(const std::string& name, int value) const;
	void SetFloat(const std::string& name, float v1, float v2, float v3, float va) const; // RGBA

private:
	// Create shaders
	unsigned int CreateShader(const std::string& vertexPath, const std::string& fragmentPath);
	// Compile shader
	unsigned int CompileShader(unsigned int type, const std::string& src);

	std::string vertexShaderSource;
	std::string fragmentShaderSource;
};