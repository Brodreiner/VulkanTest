#pragma once

#include "AmrQueueFamily.hpp"
#include <vector>

AmrQueueFamily::QueueFamilyIndices AmrQueueFamily::findBestQueueFamilieCombination(VkPhysicalDevice device, VkSurfaceKHR surface)
{
	QueueFamilyIndices queueFamilyIndices;
	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());
	int i = 0;
	for (const auto& queueFamily : queueFamilies) {
		if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
			queueFamilyIndices.graphicsFamily = i;
		}
		VkBool32 presentSupport = false;
		vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);
		if (queueFamily.queueCount > 0 && presentSupport) {
			queueFamilyIndices.presentFamily = i;
		}
		if (queueFamilyIndices.isComplete()) {
			break;
		}
		i++;
	}
	return queueFamilyIndices;
}

bool AmrQueueFamily::hasSufficientQueueFamilySupport(VkPhysicalDevice device, VkSurfaceKHR surface)
{
	return findBestQueueFamilieCombination(device, surface).isComplete();
}

AmrQueueFamily::AmrQueueFamily(VkPhysicalDevice device, VkSurfaceKHR surface)
	:m_indices(findBestQueueFamilieCombination(device, surface))
{
	if (!m_indices.isComplete())
		throw std::runtime_error("No sufficient QueueFamilie support found!");
	VkDeviceQueueCreateInfo deviceQueueCreateInfo = {};
	deviceQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	deviceQueueCreateInfo.queueFamilyIndex = m_indices.graphicsFamily;
	deviceQueueCreateInfo.queueCount = 1;
	deviceQueueCreateInfo.pQueuePriorities = &m_queuePriority;
	m_deviceQueueCreateInfo.push_back(deviceQueueCreateInfo);
	// if graphics an present queue family are not the same, add both of them
	if (m_indices.presentFamily != m_indices.graphicsFamily)
	{
		deviceQueueCreateInfo.queueFamilyIndex = m_indices.presentFamily;
		m_deviceQueueCreateInfo.push_back(deviceQueueCreateInfo);
	}
}

size_t AmrQueueFamily::getDeviceQueueCreateInfoSize() const
{
	return m_deviceQueueCreateInfo.size();
}

const VkDeviceQueueCreateInfo* AmrQueueFamily::getDeviceQueueCreateInfoData() const
{
	return m_deviceQueueCreateInfo.data();
}

uint32_t AmrQueueFamily::getGraphicsQueueFamilyIndex() const
{
	return m_indices.graphicsFamily;
}

uint32_t AmrQueueFamily::getPresentQueueFamilyIndex() const
{
	return m_indices.presentFamily;
}
