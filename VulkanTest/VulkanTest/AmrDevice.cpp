#pragma once

#include "AmrDevice.hpp"
#include <stdexcept>
#include "AmrPhysicalDevice.hpp"
#include "AmrValidationLayer.hpp"

AmrDevice& AmrDevice::operator=(AmrDevice&& other)
{
	if (m_device != VK_NULL_HANDLE)
		vkDestroyDevice(m_device, nullptr);
	m_device = other.m_device;
	other.m_device = VK_NULL_HANDLE;
	return *this;
}


AmrDevice::AmrDevice(VkPhysicalDevice physicalDevice, size_t deviceQueueCreateInfoSize, const VkDeviceQueueCreateInfo* deviceQueueCreateInfoData)
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

AmrDevice::~AmrDevice()
{
	if (m_device != VK_NULL_HANDLE)
		vkDestroyDevice(m_device, nullptr);
}

AmrDevice::operator VkDevice() const
{
	return m_device;
}
