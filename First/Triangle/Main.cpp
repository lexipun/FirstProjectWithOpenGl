#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../Colorable triangle/Shader.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


void InitializeOpenGl() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

void SetWindowSettings(GLFWwindow* &window) {
	glfwMakeContextCurrent(window); //set main window in current thread
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); //possibility chage view size

}

int main()
{
	unsigned int vertexShader;
	
		unsigned int fragmentShader;
		unsigned int fragmentShaderYellow;
	unsigned int shaderProgram;
	unsigned int shaderProgramWithYellow;
	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;
		float vertices[] = {
	 0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f, 
	-0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  
	 0.0f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f  
	};
	unsigned int indices[] = {  
		3, 4, 5, 
		1, 2, 3  
	};

	InitializeOpenGl();

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "window with triangle", NULL, NULL);

	if (window == NULL)
	{
		// std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	SetWindowSettings(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		 std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	const char* pathToVertexShader = "Shader.vs";
	const char* pathToFragmentShader = "Shader.fs";

	Shader shader = Shader(pathToVertexShader, pathToFragmentShader);



	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);


	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

		shader.use();

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		
		glBindVertexArray(VAO);
		
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
	return 0;
}


void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}