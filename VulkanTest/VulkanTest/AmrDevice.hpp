#pragma once

#include <vulkan/vulkan.h>

class AmrDevice
{
	VkDevice m_device = VK_NULL_HANDLE;

public:
	AmrDevice(VkPhysicalDevice physicalDevice, size_t deviceQueueCreateInfoSize, const VkDeviceQueueCreateInfo* deviceQueueCreateInfoData);

	~AmrDevice();

	operator VkDevice() const;
};