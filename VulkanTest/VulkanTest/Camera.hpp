#pragma once

#include <glm/vec3.hpp>
#include <glm/gtx/matrix_cross_product.hpp>
#include <glm/gtx/rotate_vector.hpp>


class Camera
{
	bool m_moveForward = false;
	bool m_moveBack = false;
	bool m_moveLeft = false;
	bool m_moveRight = false;
	bool m_isMouseLookEnabled = false;
	double m_mouseLastX;
	double m_mouseLastY;

	glm::vec3 m_position = { 128.f, 150.f, 320.0f };
	glm::vec3 m_orientation = glm::normalize(glm::vec3{ 0.0f, -0.4f, -0.8f });
	float m_moveSpeed = 30.f;
	float m_mouseSpeed = 0.004f;

public:
	glm::vec3 getPosition()
	{
		return m_position;
	}

	glm::vec3 getOrientation()
	{
		return m_orientation;
	}

	void moveForward(bool value)
	{
		m_moveForward = value;
	}
	void moveBack(bool value)
	{
		m_moveBack = value;
	}
	void moveLeft(bool value)
	{
		m_moveLeft = value;
	}
	void moveRight(bool value)
	{
		m_moveRight = value;
	}

	void enableMouseLook()
	{
		m_isMouseLookEnabled = true;
	}

	void disableMouseLook()
	{
		m_isMouseLookEnabled = false;
	}

	void mouseLook(double xpos, double ypos)
	{
		if (m_isMouseLookEnabled)
		{
			float xdiff = (float)(xpos - m_mouseLastX);
			float ydiff = (float)(ypos - m_mouseLastY);
			// left, right
			m_orientation = glm::rotate(m_orientation, -xdiff * m_mouseSpeed, glm::vec3{0, 1, 0});
			// up, down
			auto newOrientation = glm::rotate(m_orientation, -ydiff * m_mouseSpeed, glm::cross(m_orientation, glm::vec3{ 0, 1, 0 }));
			if (glm::length(newOrientation - m_orientation) < glm::length(newOrientation + glm::vec3{ 0, 1, 0 })) // prevent rollover bottom
				if (glm::length(newOrientation - m_orientation) < glm::length(newOrientation - glm::vec3{ 0, 1, 0 })) // prevent rollover top
					m_orientation = newOrientation;
		}
		m_mouseLastX = xpos;
		m_mouseLastY = ypos;
	}

	void move(float timeStep)
	{
		if(m_moveBack)
			m_position -= timeStep * m_moveSpeed * m_orientation;
		if (m_moveForward)
			m_position += timeStep * m_moveSpeed * m_orientation;
		if (m_moveLeft)
			m_position -= timeStep * m_moveSpeed * glm::normalize(glm::cross(m_orientation, { 0, 1, 0 }));
		if (m_moveRight)
			m_position += timeStep * m_moveSpeed * glm::normalize(glm::cross(m_orientation, { 0, 1, 0 }));
	}

};