#pragma once

#include <vulkan/vulkan.h>

struct GLFWwindow;

class AmrSurface
{
	GLFWwindow* m_window;
	VkInstance m_instance;
	VkSurfaceKHR m_surface;

public:
	AmrSurface(GLFWwindow* window, VkInstance instance);

	~AmrSurface();

	operator VkSurfaceKHR() const;

};
