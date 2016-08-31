#pragma once

class AmrBuffer
{
	VkDevice m_device = VK_NULL_HANDLE;
	VkBuffer m_buffer = VK_NULL_HANDLE;

public:
	AmrBuffer()
	{
	}
	AmrBuffer(const AmrBuffer&) = delete;
	AmrBuffer(AmrBuffer&&) = delete;
	AmrBuffer& operator=(const AmrBuffer&) = delete;
	AmrBuffer& operator=(AmrBuffer&& other)
	{
		std::swap(m_device, other.m_device);
		std::swap(m_buffer, other.m_buffer);
		return *this;
	}

	AmrBuffer(VkDevice device, VkDeviceSize size, VkBufferUsageFlags usage)
		:m_device(device)
	{
		VkBufferCreateInfo bufferInfo = {};
		bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bufferInfo.size = size;
		bufferInfo.usage = usage;
		bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		if (vkCreateBuffer(m_device, &bufferInfo, nullptr, &m_buffer) != VK_SUCCESS)
			throw std::runtime_error("failed to create buffer!");
	}

	~AmrBuffer()
	{
		if(m_buffer != VK_NULL_HANDLE)
			vkDestroyBuffer(m_device, m_buffer, nullptr);
	}

	VkMemoryRequirements getMemoryRequirements()
	{
		VkMemoryRequirements memoryRequirements;
		vkGetBufferMemoryRequirements(m_device, m_buffer, &memoryRequirements);
		return memoryRequirements;
	}

	operator VkBuffer() const
	{
		return m_buffer;
	}

};

