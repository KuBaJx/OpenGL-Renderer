#pragma once

#include "../StdAfx.h"

#define DEBUG
// Assert
#define ASSERT(x) if(!(x)) __debugbreak(); //__debugbreak - MSVC specific -> puts breakpoint when assert.

// 1. -> Clear all errors, 2. -> Log error into console (x) is parameter, in this case function, method, we want to check for errors
#ifdef DEBUG // Available in debug mode..
//#x - turns function to string (get function name), __FILE__ -> Gets filename, __LINE__ gets line where error occured
#define GLCall(x)GLClearError();x;ASSERT(GLLogCall(#x, __FILE__, __LINE__))
#else
#define GLCall(x)
#endif

// Clears all errors before logging another ones
void GLClearError();
// Returns current errors
bool GLLogCall(const char* function, const char* file, int line);