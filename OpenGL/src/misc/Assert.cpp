#include "Assert.h"

void GLClearError()
{
	while (glGetError());
}

bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error]: (" << error << ") on line: (" << line << ") --> " << function << "\nFile: " << file << std::endl;
		return false;
	}
	return true;
}