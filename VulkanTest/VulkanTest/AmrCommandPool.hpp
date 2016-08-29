#pragma once

class AmrCommandPool
{
	VkCommandPool m_commandPool;
	VkDevice m_device;

public:

	AmrCommandPool(const AmrCommandPool&) = delete;

	AmrCommandPool(VkDevice device, uint32_t queueFalilyIndex)
		: m_device(device)
	{
		VkCommandPoolCreateInfo poolInfo = {};
		poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		poolInfo.queueFamilyIndex = queueFalilyIndex;
		if (vkCreateCommandPool(device, &poolInfo, nullptr, &m_commandPool) != VK_SUCCESS)
			throw std::runtime_error("failed to create command pool!");
	}

	~AmrCommandPool()
	{
		vkDestroyCommandPool(m_device, m_commandPool, nullptr);
	}

	operator VkCommandPool() const
	{
		return m_commandPool;
	}

};

