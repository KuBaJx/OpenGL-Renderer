#include "StdAfx.h"

#include "renderer/VertexBuffer.h"
#include "renderer/IndexBuffer.h"
#include "renderer/VertexArray.h"
#include "renderer/VertexBufferLayout.h"

#include "Shader.h"
#include "FrameTime.h"

void OnWindowResize(GLFWwindow* window, int width, int height);
void ProcessInput(GLFWwindow* window);
float ColorModifier();

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

	glfwSetWindowSizeCallback(window, OnWindowResize);

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

	// Additional scope for proper destruction of objects
	{
		VertexBuffer vertexBuffer(positions, sizeof(positions));
		IndexBuffer  indexBuffer(indices, sizeof(indices));
	
		VertexBufferLayout vertexBufferLayout;
		vertexBufferLayout.Push<float>(3); // How many elements per one vertex
	
		VertexArray vertexArray;
		vertexArray.AddBuffer(vertexBuffer, vertexBufferLayout);
	
		Shader shader("res/shaders/shader.vs", "res/shaders/shader.fs");
		FrameTime fpsTimer;



		// LOOP
		while (!glfwWindowShouldClose(window))
		{
			fpsTimer.GetFrameTime();
			ProcessInput(window);
			glClear(GL_COLOR_BUFFER_BIT);

			float rValue = ColorModifier() + 0.2f;
			float gValue = ColorModifier();
			float bValue = ColorModifier() - 1.5f;

			GLCall(shader.Bind());
			shader.SetUniform4f("u_Color", rValue, gValue, bValue, 1.0f);

			vertexArray.BindArray();
			indexBuffer.Bind();

			//glDrawArrays(GL_TRIANGLES, 0, 6); --> not using IndexBuffer
			GLCall(glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, nullptr)); // using IndexBuffer, last property can be null since we already bound IndexBuffer above

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		vertexArray.UnbindArray();
	}
	// ~Additional scope

	glfwTerminate();
	return 0;
}

// Window resizing handler
void OnWindowResize(GLFWwindow* window, int width, int height)
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

float ColorModifier()
{
	float timeValue = glfwGetTime();
	float outValue = (sin(timeValue) / 2) + 0.5f;

	return outValue;
}