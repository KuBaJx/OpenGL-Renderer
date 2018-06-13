#include "StdAfx.h"

#include "Shader.h"

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
		 0.0f,  0.5f, 0.0f
	};

	unsigned int buffer; // Buffer ID
	glGenBuffers(1, &buffer); // Vygeneruje buffer a referecuje ho do premenneh buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffer); // Prideli array buffer to premmnej buffer
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(buffer), positions, GL_STATIC_DRAW); // 

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	Shader shader("src/shaders/shader.vs", "src/shaders/shader.fs");

	// LOOP
	while (!glfwWindowShouldClose(window))
	{
		ProcessInput(window);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.Use();
		shader.SetFloat("u_Color", 0.5f, 0.5f, 1.0f, 1.0f);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
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