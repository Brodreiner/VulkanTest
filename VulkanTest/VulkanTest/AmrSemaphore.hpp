#pragma once

#include <vulkan/vulkan.h>

class AmrSemaphore
{
	VkDevice m_device = VK_NULL_HANDLE;
	VkSemaphore m_semaphore = VK_NULL_HANDLE;

public:

	AmrSemaphore(VkDevice device);

	~AmrSemaphore();

	operator VkSemaphore() const;
};
