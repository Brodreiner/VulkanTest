#pragma once

#include "AmrWindow.hpp"
#include <GLFW/glfw3.h>
#include <iostream>

AmrWindow& AmrWindow::operator=(AmrWindow&& other)
{
	m_eventLoopCallback = other.m_eventLoopCallback;
	m_resizeCallback = other.m_resizeCallback;
	m_window = other.m_window;
	glfwSetWindowUserPointer(m_window, this);
	return *this;
}

void AmrWindow::onWindowResized(GLFWwindow* window, int width, int height)
{
	AmrWindow* app = reinterpret_cast<AmrWindow*>(glfwGetWindowUserPointer(window));
	app->m_resizeCallback(width, height);
}

void AmrWindow::onKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	AmrWindow* app = reinterpret_cast<AmrWindow*>(glfwGetWindowUserPointer(window));
	app->m_keyCallback(key, scancode, action, mods);
}

void AmrWindow::onMouseMove(GLFWwindow* window, double xpos, double ypos)
{
	AmrWindow* app = reinterpret_cast<AmrWindow*>(glfwGetWindowUserPointer(window));
	app->m_mouseMoveCallback(xpos, ypos);
}

void AmrWindow::onMouseClick(GLFWwindow* window, int button, int action, int mods)
{
	AmrWindow* app = reinterpret_cast<AmrWindow*>(glfwGetWindowUserPointer(window));
	app->m_mouseClickCallback(button, action, mods);
}
void AmrWindow::defaultResizeCallback(int width, int height)
{
	std::cout << "Window resized: " << width << "x" << height << std::endl;
}

AmrWindow::AmrWindow(uint32_t width, uint32_t height, const std::string& title)
{
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	glfwSetWindowUserPointer(m_window, this);
	glfwSetWindowSizeCallback(m_window, AmrWindow::onWindowResized);
	glfwSetKeyCallback(m_window, AmrWindow::onKeyEvent);
	glfwSetCursorPosCallback(m_window, AmrWindow::onMouseMove);
	glfwSetMouseButtonCallback(m_window, AmrWindow::onMouseClick);
}

void AmrWindow::mainLoop()
{
	while (!glfwWindowShouldClose(m_window))
	{
		glfwPollEvents();
		m_eventLoopCallback();
	}
}
void AmrWindow::setResizeCallback(std::function<void(int, int)> callback)
{
	m_resizeCallback = callback;
}
void AmrWindow::setEventLoopCallback(std::function<void()> callback)
{
	m_eventLoopCallback = callback;
}

void AmrWindow::setKeyCallback(std::function<void(int, int, int, int)> callback)
{
	m_keyCallback = callback;
}

void AmrWindow::setMouseMoveCallback(std::function<void(double, double)> callback)
{
	m_mouseMoveCallback = callback;
}

void AmrWindow::setMouseClickCallback(std::function<void(int, int, int)> callback)
{
	m_mouseClickCallback = callback;
}

void AmrWindow::disableCursor()
{
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void AmrWindow::enableCursor()
{
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

AmrWindow::operator GLFWwindow*() const
{
	return m_window;
}
