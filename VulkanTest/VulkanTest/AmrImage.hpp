#pragma once

#include <vulkan/vulkan.h>

class AmrPhysicalDevice;

class AmrImage
{
	VkImage m_image = VK_NULL_HANDLE;
	VkDeviceMemory m_deviceMemory = VK_NULL_HANDLE;
	VkDevice m_device = VK_NULL_HANDLE;

	void createImage(const AmrPhysicalDevice& amrPhysicalDevice, VkExtent2D extent, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties);

public:
	AmrImage() = default;
	AmrImage(const AmrImage&) = delete;
	AmrImage(AmrImage&&) = delete;
	AmrImage& operator=(const AmrImage&) = delete;
	AmrImage& operator=(AmrImage&& other);
	~AmrImage();

	AmrImage(const AmrPhysicalDevice& amrPhysicalDevice, VkDevice device, VkExtent2D extent, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties);


	void writeData(const void* pixels, size_t imageSize);

	operator VkImage() const;

};