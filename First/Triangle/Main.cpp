#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<iostream>


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

void SetVertexShader(unsigned int& vertexShader) {

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

	int  success;
	char infoLog[512];

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;

		delete[] infoLog;
	}
}
void SetFragmentShader(unsigned int& fragmentShader) {

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
"}\n\0";

	int  success;
	char infoLog[512];

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;

		delete[] infoLog;
	}
}
void SetFragmentShaderYellow(unsigned int& fragmentShader) {

	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"uniform vec4 ourColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = ourColor;\n"
		"}\n\0";

	int  success;
	char infoLog[512];



	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;

		delete[] infoLog;
	}
}
void AttachShaders(unsigned int& shaderProgram, unsigned int& vertexShader, unsigned int& fragmentShader) {
	int  success;
	char infoLog[512];

	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;

		 delete[] infoLog;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

void Render(unsigned int& shaderProgramYellow,unsigned int& shaderProgram, unsigned int &VAO, unsigned int &EBO ) {
	float timeValue = glfwGetTime();
	float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
	int vertexColorLocation = glGetUniformLocation(shaderProgramYellow, "ourColor");

	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);


	glUseProgram(shaderProgramYellow);
	glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	//		glUseProgram(shaderProgramYellow);
	glUseProgram(shaderProgram);

	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

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
			 0.5f,  0.5f, 0.0f,  
			 0.5f, -0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f, 


			-0.5f,  0.5f, 0.0f,
			0.5f, 0.6f, 0.0f,
			-0.5f, -0.4f, 0.0f,
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

	SetVertexShader(vertexShader);
	SetFragmentShader(fragmentShader);
	SetFragmentShaderYellow(fragmentShaderYellow);



	AttachShaders(shaderProgram, vertexShader, fragmentShader);
	AttachShaders(shaderProgramWithYellow, vertexShader, fragmentShaderYellow);


	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);


	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		Render(shaderProgramWithYellow, shaderProgram, VAO, EBO);
		
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