#pragma once

#include <vulkan/vulkan.h>

class AmrDeviceMemory
{
	VkDevice m_device = VK_NULL_HANDLE;
	VkDeviceMemory m_deviceMemory = VK_NULL_HANDLE;

	uint32_t findMemoryType(VkPhysicalDevice physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties);

public:
	AmrDeviceMemory();
	AmrDeviceMemory(const AmrDeviceMemory&) = delete;
	AmrDeviceMemory(AmrDeviceMemory&&) = delete;
	AmrDeviceMemory& operator=(const AmrDeviceMemory&) = delete;
	AmrDeviceMemory& operator=(AmrDeviceMemory&& other);


	AmrDeviceMemory(VkPhysicalDevice physicalDevice, VkDevice device, VkMemoryRequirements memoryRequirements, VkMemoryPropertyFlags memoryPropertyFlags);

	~AmrDeviceMemory();

	void writeData(const void* data, size_t size);

	operator VkDeviceMemory() const;
};