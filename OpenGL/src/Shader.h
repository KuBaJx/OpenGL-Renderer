#pragma once

#include "StdAfx.h"

class Shader
{
public:
	// Constructor - reads and builds shader
	Shader(const char* vertexPath, const char* fragmentPath);

	// Use / Activate shader
	void Use();
	void Delete();

	// Uniform functions
	void SetFloat(const std::string& name, float v1, float v2, float v3, float va) const; // RGBA

private:
	// Create shaders
	unsigned int CreateShader(const std::string& vertexPath, const std::string& fragmentPath);
	// Compile shader
	unsigned int CompileShader(unsigned int type, const std::string& src);

private:
	unsigned int m_RendererID; // Shader program ID
};