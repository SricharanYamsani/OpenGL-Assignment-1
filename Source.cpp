#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>

#include<iostream>
#include<vector>

#include "Shapes.h"

const int SCR_WIDTH = 800, SCR_HEIGHT = 600;


bool secondPoint = false;

//float vertices[100];
std::vector<glm::vec2> vertices;
int n = 0;

glm::vec2 points[2] = {glm::vec2(0.0f,0.0f),glm::vec2(0.0f,0.0f)};

//Circle Parameters
const float angleDiff = 10.0f;
float radius = 0.5f;

//

//Circle *c = new Circle();


const char* vertexShaderSource =
"#version 330 core"
"\nlayout(location = 0)in vec2 aPos;"
"\nvoid main(){\n"
"gl_Position = vec4(aPos.x,aPos.y,0.0f,1.0f);}\0";


const char* fragmentShaderSource =
"#version 330 core"
"\nvoid main(){\n"
"gl_FragColor = vec4(1.0f,0.0f,0.0f,1.0f);}\0";


bool firstClick = true;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

void drawCircle();

int main()

{

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwInit();

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Paint Program", NULL, NULL);

	glfwMakeContextCurrent(window);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW Init Failed";

		glfwTerminate();

		exit(-1);

	}

	unsigned int vertexShader, fragmentShader;

	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vertexShaderSource, 0);

	glCompileShader(vertexShader);


	int success;

	char infoLog[512];


	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, 0, infoLog);

		std::cout << "\nVertex Shader Compilation Failed\n" << infoLog;
	}


	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader, 1, &fragmentShaderSource, 0);

	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, 0, infoLog);

		std::cout << "\nFragmnet Shader Compilation Failed\n" << infoLog;
	}


	unsigned int shaderProg;

	shaderProg = glCreateProgram();

	glAttachShader(shaderProg, vertexShader);

	glAttachShader(shaderProg, fragmentShader);

	glLinkProgram(shaderProg);

	glGetProgramiv(shaderProg, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(shaderProg, 512, 0, infoLog);

		std::cout << "\nShader Program Linking Failed\n" << infoLog;
	}

	glDeleteShader(vertexShader);

	glDeleteShader(fragmentShader);

	glUseProgram(shaderProg);

	/*
	drawCircle();


	unsigned int VAO, VBO;

	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), vertices.data(), GL_STATIC_DRAW);


	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(0);

	*/
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//std::cout << vertices.size();


	Circle C;
	C.SetAngleDiff(angleDiff);
	/*
	c->SetOriginPosition(glm::vec2(0.0f, 0.0f));
	c->SetCirclePosition(glm::vec2(radius, 0.0f));
	c->SetAngleDiff(angleDiff);
	*/

	while (!glfwWindowShouldClose(window))
	{

		glClearColor(1.0f, 1.0f, 0.0, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT);


		processInput(window);

		/*
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), vertices.data(), GL_STATIC_DRAW);


		glPointSize(5.0);

		glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size());*/

		C.SetOriginPosition(points[0]);
		C.SetCirclePosition(points[1]);
		C.draw();
		

		glfwSwapBuffers(window);

		glfwPollEvents();

	}

	/*
	glDeleteBuffers(1, &VBO);

	glDeleteVertexArrays(1, &VAO);*/

	glfwTerminate();

	return 0;
}



void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{

	glViewport(0, 0, width, height);

}



void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwTerminate();

		exit(0);
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		//std::cout << "In Release";
		firstClick = true;
		
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		double xpos, ypos;
		if (firstClick)
		{
			glfwGetCursorPos(window, &xpos, &ypos);

			std::cout << "\nCursor Position : (" << xpos << " : " << ypos << ")" << std::endl;

			firstClick = false;


			float x = (xpos - SCR_WIDTH / 2.0) / (SCR_WIDTH / 2.0);

			float y = -(ypos - SCR_HEIGHT / 2.0) / (SCR_HEIGHT / 2.0);


			vertices.push_back(glm::vec2(x, y));


			std::cout << x << "\t" << y << "\t" << SCR_WIDTH << "\t" << SCR_HEIGHT << "\tSize:" << vertices.size();
		
			if (secondPoint)
			{
				points[1] = glm::vec2(x, y);
				std::cout << "Circl Point Given";
			}
			else
			{
				points[0] = glm::vec2(x, y);
				points[1] = glm::vec2(x, y);
			}
			secondPoint = !secondPoint;

		}

	}


}



void drawCircle()

{

	glm::vec2 point = glm::vec2(0.0f, 0.0f);

	//vertices.push_back(point);

	for (float i = 0.0f; i < 360.0f; i += angleDiff)
	{

		point.x = cos(i * 3.14f / 180.0f) * radius;

		point.y = sin(i * 3.14f / 180.0f) * radius * SCR_WIDTH / SCR_HEIGHT;


		vertices.push_back(point);
	}

	vertices.push_back(glm::vec2(radius, 0.0f));

}
