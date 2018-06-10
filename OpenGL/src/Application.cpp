#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void ProcessInput(GLFWwindow* window);

int main()
{
	GLFWwindow* window;

	if (!glfwInit())
	{
		return -1;
	}
	glfwInit();

	window = glfwCreateWindow(800, 600, "OpenGL Renderer", nullptr, nullptr);
	if (!window)
	{
		std::cerr << "Error! Failed to create GLFW window!" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Init GLEW - Needs valid OpenGL context
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Error! Failed to intialize GLEW!" << std::endl;
	}

	// Get OpenGL version
	std::cout << "OpenGL VERSION: [" << glGetString(GL_VERSION) << "]" << std::endl;

	glfwSetWindowSizeCallback(window, framebuffer_size_callback);

	while (!glfwWindowShouldClose(window))
	{
		ProcessInput(window);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

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