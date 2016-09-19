#pragma once

#include <vulkan/vulkan.h>

class AmrCommandBuffer
{
	VkDevice m_device = VK_NULL_HANDLE;
	VkCommandPool m_commandPool = VK_NULL_HANDLE;
	VkCommandBuffer m_commandBuffer = VK_NULL_HANDLE;

public:
	AmrCommandBuffer() {};
	AmrCommandBuffer(const AmrCommandBuffer&) = delete;
	AmrCommandBuffer(AmrCommandBuffer&&) = delete;
	AmrCommandBuffer& operator=(const AmrCommandBuffer&) = delete;
	AmrCommandBuffer& operator=(AmrCommandBuffer&& other);

	AmrCommandBuffer(VkDevice device, VkCommandPool commandPool, VkCommandBufferLevel commandBufferLevel);

	~AmrCommandBuffer();

	void begin(VkCommandBufferUsageFlags flags);

	void end();

	void submit(VkQueue queue);

	operator VkCommandBuffer() const;

};