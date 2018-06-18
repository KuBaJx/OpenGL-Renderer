#include "StdAfx.h"
#include "Shader.h"
#include "FrameTime.h"

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

	glfwSwapInterval(1); // VSYNC

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

	// VertexBufferObject
	unsigned int vao;
	GLCall(glGenVertexArrays(1, &vao));
	GLCall(glBindVertexArray(vao));

	unsigned int buffer; // Buffer ID
	glGenBuffers(1, &buffer); // Generate vertex array buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffer); // bind array buffer to id
	glBufferData(GL_ARRAY_BUFFER, 4 * 3 * sizeof(buffer), positions, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	// Links buffer with VAO - so we can use multiple buffers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	
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

		GLCall(shader.Use());
		GLCall(shader.SetFloat("u_Color", 0.3f, 0.5f, 1.0f, 1.0f));

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
