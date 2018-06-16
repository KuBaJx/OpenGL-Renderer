#include "StdAfx.h"
#include "Shader.h"
#include "FrameTime.h"

// ------------------------ // 
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

// Clear all errors before logging another ones
static void GLClearError()
{
	while (glGetError());
}

// Returs current errors
static bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error]: (" << error << ") on line: (" << line << ") --> " << function << "\nFile: " << file << std::endl;
		return false;
	}
	return true;
}
// ------------------------ // 

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void ProcessInput(GLFWwindow* window);

const unsigned int sWidth = 800;
const unsigned int sHeight = 600;


int main()
{
	GLFWwindow* window;

	glfwInit();

	window = glfwCreateWindow(sWidth, sHeight, "OpenGL Renderer", nullptr, nullptr);
	if (!window)
	{
		std::cerr << "Failed to create GLFW window!" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glfwSetWindowSizeCallback(window, framebuffer_size_callback);

	if (!glewInit() == GLEW_OK)
	{
		std::cerr << "Failed to initialize GLEW!" << std::endl;
		return -1;
	}

	std::cout << "OpenGL version: [" << glGetString(GL_VERSION) << "]" << std::endl;

	float positions[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
	    -0.5f,  0.5f, 0.0f
	};

	// Index buffer
	unsigned int indices[] = {
		0, 1, 2, // 1st triangle
		2, 3, 0	// 2nd triangle
	};

	unsigned int buffer; // Buffer ID
	glGenBuffers(1, &buffer); // Vygeneruje buffer a referecuje ho do premennej buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffer); // Prideli array buffer to premmnej buffer
	glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(buffer), positions, GL_STATIC_DRAW); // 

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	// IndexBufferObject
	unsigned int ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	Shader shader("res/shaders/shader.vs", "res/shaders/shader.fs");
	FrameTime fpsTimer;

	// LOOP
	while (!glfwWindowShouldClose(window))
	{
		fpsTimer.GetFrameTime();
		ProcessInput(window);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.Use();
		shader.SetFloat("u_Color", 0.5f, 0.5f, 1.0f, 1.0f);

		//glDrawArrays(GL_TRIANGLES, 0, 6); --> not using IndexBuffer
		GLCall(glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, nullptr)); // using IndexBuffer, last property can be null since we already bound IndexBuffer above

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	shader.Delete();
	glfwTerminate();
	return 0;
}

// Window resizing handler
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}