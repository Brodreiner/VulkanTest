#pragma once

#include <vulkan/vulkan.h>

struct GLFWwindow;

class AmrSurface
{
	GLFWwindow* m_window = nullptr;
	VkInstance m_instance = VK_NULL_HANDLE;
	VkSurfaceKHR m_surface = VK_NULL_HANDLE;

public:
	AmrSurface(GLFWwindow* window, VkInstance instance);

	~AmrSurface();

	operator VkSurfaceKHR() const;

};
