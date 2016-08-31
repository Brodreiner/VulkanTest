#pragma once

class AmrDeviceMemory
{
	VkDevice m_device = VK_NULL_HANDLE;
	VkDeviceMemory m_deviceMemory = VK_NULL_HANDLE;

	uint32_t findMemoryType(VkPhysicalDevice physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties) {
		VkPhysicalDeviceMemoryProperties memProperties;
		vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);

		for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
			if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
				return i;
			}
		}

		throw std::runtime_error("failed to find suitable memory type!");
	}

public:
	AmrDeviceMemory()
	{
	}
	AmrDeviceMemory(const AmrDeviceMemory&) = delete;
	AmrDeviceMemory(AmrDeviceMemory&&) = delete;
	AmrDeviceMemory& operator=(const AmrDeviceMemory&) = delete;
	AmrDeviceMemory& operator=(AmrDeviceMemory&&) = delete;


	AmrDeviceMemory(VkPhysicalDevice physicalDevice, VkDevice device, VkMemoryRequirements memoryRequirements, VkMemoryPropertyFlags memoryPropertyFlags)
		: m_device(device)
	{
		VkMemoryAllocateInfo allocInfo = {};
		allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		allocInfo.allocationSize = memoryRequirements.size;
		allocInfo.memoryTypeIndex = findMemoryType(physicalDevice, memoryRequirements.memoryTypeBits, memoryPropertyFlags);
		if (vkAllocateMemory(device, &allocInfo, nullptr, &m_deviceMemory) != VK_SUCCESS)
			throw std::runtime_error("failed to allocate Vulkan memory!");
	}

	~AmrDeviceMemory()
	{
		if(m_deviceMemory != VK_NULL_HANDLE)
			vkFreeMemory(m_device, m_deviceMemory, nullptr);
	}

	operator VkDeviceMemory() const
	{
		return m_deviceMemory;
	}
};