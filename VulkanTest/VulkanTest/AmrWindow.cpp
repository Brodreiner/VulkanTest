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

AmrWindow::operator GLFWwindow*() const
{
	return m_window;
}
