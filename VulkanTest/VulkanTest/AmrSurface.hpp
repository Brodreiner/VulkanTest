#pragma once

class AmrSurface
{
	GLFWwindow* m_window;
	VkInstance m_instance;
	VkSurfaceKHR m_surface;

public:
	AmrSurface(GLFWwindow* window, VkInstance instance)
		:m_window(window), m_instance(instance)
	{
		if (glfwCreateWindowSurface(m_instance, m_window, nullptr, &m_surface) != VK_SUCCESS)
			throw std::runtime_error("failed to create window surface!");
	}

	~AmrSurface()
	{
		vkDestroySurfaceKHR(m_instance, m_surface, nullptr);
	}

	operator VkSurfaceKHR() const
	{
		return m_surface;
	}

};
