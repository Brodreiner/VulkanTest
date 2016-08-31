#pragma once

class AmrSemaphore
{
	VkDevice m_device;
	VkSemaphore m_semaphore;

public:

	AmrSemaphore(VkDevice device)
		: m_device(device)
	{
		VkSemaphoreCreateInfo semaphoreInfo = {};
		semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
		if (vkCreateSemaphore(device, &semaphoreInfo, nullptr, &m_semaphore) != VK_SUCCESS)
			throw std::runtime_error("failed to create semaphore!");
	}

	~AmrSemaphore()
	{
		vkDestroySemaphore(m_device, m_semaphore, nullptr);
	}

	operator VkSemaphore() const
	{
		return m_semaphore;
	}
};
