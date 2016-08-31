#pragma once

class AmrQueue
{
	VkQueue m_queue;
	VkDevice m_device;
public:
	AmrQueue(VkDevice device, uint32_t queueFamily, uint32_t index)
		:m_device(device)
	{
		vkGetDeviceQueue(m_device, queueFamily, index, &m_queue);
	}

	operator VkQueue() const
	{
		return m_queue;
	}
};