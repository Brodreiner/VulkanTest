#pragma once

#include <vulkan/vulkan.h>

class AmrCommandPool
{
	VkCommandPool m_commandPool;
	VkDevice m_device;

public:

	AmrCommandPool(const AmrCommandPool&) = delete;

	AmrCommandPool(VkDevice device, uint32_t queueFalilyIndex);

	~AmrCommandPool();

	void transitionImageLayout(VkQueue graphicsQueue, VkImage image, VkImageLayout oldLayout, VkImageLayout newLayout) const;

	void copyImage(VkQueue graphicsQueue, VkImage srcImage, VkImage dstImage, VkExtent2D extent) const;

	void copyBuffer(VkQueue queue, VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size) const;

	operator VkCommandPool() const;

};

