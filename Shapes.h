#pragma once
#include<GL/glew.h>
#include<vector>
#include<glm.hpp>

class Shape
{
protected:
	unsigned int VAO, VBO;

public:
	Shape()
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
	}
	~Shape()
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}
};

class Circle : public Shape
{
	glm::vec2 positions[2];
	std::vector<glm::vec2> vertices;
	float angleDiff;
public:
	Circle()
	{
		positions[0] = positions[1] = glm::vec2(0.0f, 0.0f);
		angleDiff = 30.0f;
	}
	~Circle()
	{

	}

	void SetPositions(glm::vec2 centre, glm::vec2 circumfernce_point)
	{
		positions[0] = centre;
		positions[1] = circumfernce_point;
	}
	void SetAngleDiff(float diff)
	{
		angleDiff = diff;
	}
	void SetBufferData()
	{
		float radius = glm::distance(positions[0], positions[1]);
		glm::vec2 point = glm::vec2(0.0f,0.0f);
		for (float i = 0.0f; i < 360.0f; i += angleDiff)
		{
			point.x = cos(glm::radians(i))*radius;
			point.y = sin(glm::radians(i))*radius;

			vertices.push_back(point);
		}
		vertices.push_back(glm::vec2(radius, 0.0f));
	}
};