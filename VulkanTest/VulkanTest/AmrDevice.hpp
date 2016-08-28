#pragma once

class AmrDevice
{
	VkDevice m_device;

public:
	AmrDevice(VkPhysicalDevice physicalDevice, size_t deviceQueueCreateInfoSize, const VkDeviceQueueCreateInfo* deviceQueueCreateInfoData)
	{
		VkPhysicalDeviceFeatures deviceFeatures = {};

		VkDeviceCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

		createInfo.pQueueCreateInfos = deviceQueueCreateInfoData;
		createInfo.queueCreateInfoCount = (uint32_t)deviceQueueCreateInfoSize;

		createInfo.pEnabledFeatures = &deviceFeatures;

		createInfo.enabledExtensionCount = AmrPhysicalDevice::getDeviceExtensionSize();
		createInfo.ppEnabledExtensionNames = AmrPhysicalDevice::getDeviceExtensionData();

		createInfo.enabledLayerCount = AmrValidationLayer::size();
		createInfo.ppEnabledLayerNames = AmrValidationLayer::data();

		if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &m_device) != VK_SUCCESS) {
			throw std::runtime_error("failed to create logical device!");
		}
	}

	~AmrDevice()
	{
		vkDestroyDevice(m_device, nullptr);
	}

	operator VkDevice() const
	{
		return m_device;
	}
};