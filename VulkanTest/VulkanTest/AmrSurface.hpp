#pragma once

#include <vulkan/vulkan.h>

struct GLFWwindow;

class AmrSurface
{
	GLFWwindow* m_window = nullptr;
	VkInstance m_instance = VK_NULL_HANDLE;
	VkSurfaceKHR m_surface = VK_NULL_HANDLE;

public:
	AmrSurface() = default;
	AmrSurface(const AmrSurface&) = delete;
	AmrSurface(AmrSurface&&) = delete;
	AmrSurface& operator=(const AmrSurface&) = delete;
	AmrSurface& operator=(AmrSurface&& other);
	~AmrSurface();

	AmrSurface(GLFWwindow* window, VkInstance instance);

	operator VkSurfaceKHR() const;

};
