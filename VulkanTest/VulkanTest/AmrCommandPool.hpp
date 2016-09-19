#pragma once

#include <vulkan/vulkan.h>

class AmrCommandPool
{
	VkCommandPool m_commandPool = VK_NULL_HANDLE;
	VkDevice m_device = VK_NULL_HANDLE;

public:
	AmrCommandPool() {};
	AmrCommandPool(const AmrCommandPool&) = delete;
	AmrCommandPool(AmrCommandPool&&) = delete;
	AmrCommandPool& operator=(const AmrCommandPool&) = delete;
	AmrCommandPool& operator=(AmrCommandPool&& other);

	AmrCommandPool(VkDevice device, uint32_t queueFalilyIndex);

	~AmrCommandPool();

	void transitionImageLayout(VkQueue graphicsQueue, VkImage image, VkImageLayout oldLayout, VkImageLayout newLayout) const;

	void copyImage(VkQueue graphicsQueue, VkImage srcImage, VkImage dstImage, VkExtent2D extent) const;

	void copyBuffer(VkQueue queue, VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size) const;

	operator VkCommandPool() const;

};

