#pragma once

#include "AmrQueue.hpp"

AmrQueue::AmrQueue(VkDevice device, uint32_t queueFamily, uint32_t index)
	:m_device(device)
{
	vkGetDeviceQueue(m_device, queueFamily, index, &m_queue);
}

AmrQueue::operator VkQueue() const
{
	return m_queue;
}
