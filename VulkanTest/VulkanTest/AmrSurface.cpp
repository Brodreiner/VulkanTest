#pragma once

#include "AmrSurface.hpp"
#include <GLFW/glfw3.h>
#include <stdexcept>

AmrSurface::AmrSurface(GLFWwindow* window, VkInstance instance)
	:m_window(window), m_instance(instance)
{
	if (glfwCreateWindowSurface(m_instance, m_window, nullptr, &m_surface) != VK_SUCCESS)
		throw std::runtime_error("failed to create window surface!");
}

AmrSurface::~AmrSurface()
{
	vkDestroySurfaceKHR(m_instance, m_surface, nullptr);
}

AmrSurface::operator VkSurfaceKHR() const
{
	return m_surface;
}

