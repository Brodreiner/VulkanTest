#pragma once

#include <vulkan/vulkan.h>

class AmrCommandBuffer
{
	VkDevice m_device;
	VkCommandPool m_commandPool;
	VkCommandBuffer m_commandBuffer;

public:
	AmrCommandBuffer(VkDevice device, VkCommandPool commandPool, VkCommandBufferLevel commandBufferLevel);

	~AmrCommandBuffer();

	void begin(VkCommandBufferUsageFlags flags);

	void end();

	void submit(VkQueue queue);

	operator VkCommandBuffer() const;

};