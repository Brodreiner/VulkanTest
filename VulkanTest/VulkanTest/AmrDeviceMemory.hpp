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
	AmrDeviceMemory& operator=(AmrDeviceMemory&& other)
	{
		std::swap(m_device, other.m_device);
		std::swap(m_deviceMemory, other.m_deviceMemory);
		return *this;
	}


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

	void writeData(const void* data, size_t size)
	{
		if (data == nullptr)
			throw std::runtime_error("Texture cannot be copied, because source has no data!");
		if (m_deviceMemory == VK_NULL_HANDLE)
			throw std::runtime_error("Texture cannot be copied, because dest is not alloccated!");
		void* bufferPtr;
		vkMapMemory(m_device, m_deviceMemory, 0, static_cast<VkDeviceSize>(size), 0, &bufferPtr);
		memcpy(bufferPtr, data, size);
		vkUnmapMemory(m_device, m_deviceMemory);
	}

	operator VkDeviceMemory() const
	{
		return m_deviceMemory;
	}
};