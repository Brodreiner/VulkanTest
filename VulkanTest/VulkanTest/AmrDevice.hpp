#pragma once

#include <vulkan/vulkan.h>

class AmrDevice
{
	VkDevice m_device = VK_NULL_HANDLE;

public:
	AmrDevice() {};
	AmrDevice(const AmrDevice&) = delete;
	AmrDevice(AmrDevice&&) = delete;
	AmrDevice& operator=(const AmrDevice&) = delete;
	AmrDevice& operator=(AmrDevice&& other);

	AmrDevice(VkPhysicalDevice physicalDevice, size_t deviceQueueCreateInfoSize, const VkDeviceQueueCreateInfo* deviceQueueCreateInfoData);

	~AmrDevice();

	operator VkDevice() const;
};