#pragma once
#include<GL/glew.h>
#include<vector>
#include<glm/glm.hpp>

class Shape
{
protected:
	unsigned int VAO, VBO;

public:
	Shape()
	{
		std::cout << "In shape COnstuctor\n";
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
	}
	~Shape()
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}

	virtual void draw() = 0;
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

	void SetOriginPosition(glm::vec2 centre)
	{
		positions[0] = centre;
		//positions[1] = circumfernce_point;
	}

	void SetCirclePosition(glm::vec2 circumfernce_point)
	{
	//positions[0] = centre;
	positions[1] = circumfernce_point;
	}

	void SetAngleDiff(float diff)
	{
		angleDiff = diff;
	}

	void SetBufferData()
	{
		vertices.clear();
		float radius = glm::distance(positions[0], positions[1]);
		glm::vec2 point = positions[0];
		vertices.push_back(point);
		for (float i = 0.0f; i < 360.0f; i += angleDiff)
		{
			point.x = positions[0].x + cos(glm::radians(i))*radius;
			point.y = positions[0].y + sin(glm::radians(i))*radius;

			vertices.push_back(point);
		}
		vertices.push_back(positions[0] + glm::vec2(radius, 0.0f));
	}

	void draw()
	{
		if (positions[0] != positions[1])
		{
			SetBufferData();

			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), vertices.data(), GL_STATIC_DRAW);

			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);

			glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size());

			glBindVertexArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
		else
		{
			//std::cout << "Center is Same as Circle Point";
		}
	}
};
