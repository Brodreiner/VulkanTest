#pragma once

#include "AmrSurface.hpp"
#include <GLFW/glfw3.h>
#include <stdexcept>

AmrSurface& AmrSurface::operator=(AmrSurface&& other)
{
	if (m_surface != VK_NULL_HANDLE)
		vkDestroySurfaceKHR(m_instance, m_surface, nullptr);
	m_instance = other.m_instance;
	m_surface = other.m_surface;
	m_window = other.m_window;
	other.m_surface = VK_NULL_HANDLE;
	return *this;
}

AmrSurface::AmrSurface(GLFWwindow* window, VkInstance instance)
	:m_window(window), m_instance(instance)
{
	if (glfwCreateWindowSurface(m_instance, m_window, nullptr, &m_surface) != VK_SUCCESS)
		throw std::runtime_error("failed to create window surface!");
}

AmrSurface::~AmrSurface()
{
	if (m_surface != VK_NULL_HANDLE)
		vkDestroySurfaceKHR(m_instance, m_surface, nullptr);
}

AmrSurface::operator VkSurfaceKHR() const
{
	return m_surface;
}

