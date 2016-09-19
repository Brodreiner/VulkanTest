#pragma once

#include <vulkan/vulkan.h>

class AmrBuffer
{
	VkDevice m_device = VK_NULL_HANDLE;
	VkBuffer m_buffer = VK_NULL_HANDLE;

public:
	AmrBuffer() {};
	AmrBuffer(const AmrBuffer&) = delete;
	AmrBuffer(AmrBuffer&&) = delete;
	AmrBuffer& operator=(const AmrBuffer&) = delete;
	AmrBuffer& operator=(AmrBuffer&& other);

	AmrBuffer(VkDevice device, VkDeviceSize size, VkBufferUsageFlags usage);

	~AmrBuffer();

	VkMemoryRequirements getMemoryRequirements();

	operator VkBuffer() const;

};

