#pragma once

#include <vulkan/vulkan.h>

class AmrSemaphore
{
	VkDevice m_device = VK_NULL_HANDLE;
	VkSemaphore m_semaphore = VK_NULL_HANDLE;

public:
	AmrSemaphore() = default;
	AmrSemaphore(const AmrSemaphore&) = delete;
	AmrSemaphore(AmrSemaphore&&) = delete;
	AmrSemaphore& operator=(const AmrSemaphore&) = delete;
	AmrSemaphore& operator=(AmrSemaphore&& other);
	~AmrSemaphore();

	AmrSemaphore(VkDevice device);

	operator VkSemaphore() const;
};
