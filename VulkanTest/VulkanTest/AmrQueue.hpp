#pragma once

#include <vulkan/vulkan.h>

class AmrQueue
{
	VkQueue m_queue = VK_NULL_HANDLE;
	VkDevice m_device = VK_NULL_HANDLE;
public:
	AmrQueue(VkDevice device, uint32_t queueFamily, uint32_t index);

	operator VkQueue() const;
};