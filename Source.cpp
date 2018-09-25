#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<glm.hpp>

#include<iostream>
#include<vector>

#include "Shapes.h"

//const int SCR_WIDTH = 800, SCR_HEIGHT = 600;

enum Shape_Type
{
	LINE,RECTANGLE,CIRCLE
};

Shape_Type current = CIRCLE;

std::vector<Shape*> shapes;

Shape *C;

bool secondPoint = false;


glm::vec2 points[2] = { glm::vec2(0.0f,0.0f),glm::vec2(0.0f,0.0f) };

//Circle Parameters
const float angleDiff = 10.0f;
float radius = 0.5f;

//


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

Shape* ShapeFactory();

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

	

	C = ShapeFactory();
	

	while (!glfwWindowShouldClose(window))
	{

		glClearColor(1.0f, 1.0f, 0.0, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT);


		processInput(window);

		

		C->SetOriginPosition(points[0]);
		C->SetOtherPosition(points[1]);
		C->draw();

		
		glfwSwapBuffers(window);

		glfwPollEvents();

	}

	
	

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
		double xpos, ypos;
		//std::cout << "In Release";
		firstClick = true;
		if (secondPoint)
		{
			glfwGetCursorPos(window, &xpos, &ypos);

			//std::cout << "\nCursor Position : (" << xpos << " : " << ypos << ")" << std::endl;

			float x = (xpos - SCR_WIDTH / 2.0) / (SCR_WIDTH / 2.0);

			float y = -(ypos - SCR_HEIGHT / 2.0) / (SCR_HEIGHT / 2.0) ;

			
			points[1] = glm::vec2(x , y) ;

		}

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

			
			if (secondPoint)
			{
				points[1] = glm::vec2(x , y ) ;
				std::cout << "Second Point Given";
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

Shape* ShapeFactory()
{
	if (current == LINE)
		return new Line();
	else if (current == RECTANGLE)
		return new Rectangle();
	else if (current == CIRCLE)
		return new Circle();
	else
		return new Line();
}


