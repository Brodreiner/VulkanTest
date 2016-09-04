#pragma once

#include <vulkan/vulkan.h>

class AmrQueue
{
	VkQueue m_queue;
	VkDevice m_device;
public:
	AmrQueue(VkDevice device, uint32_t queueFamily, uint32_t index);

	operator VkQueue() const;
};