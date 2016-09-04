#pragma once

#include <vulkan/vulkan.h>

class AmrSemaphore
{
	VkDevice m_device;
	VkSemaphore m_semaphore;

public:

	AmrSemaphore(VkDevice device);

	~AmrSemaphore();

	operator VkSemaphore() const;
};
