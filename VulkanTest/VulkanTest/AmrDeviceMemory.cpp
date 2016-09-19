#pragma once

#include "AmrDeviceMemory.hpp"
#include <stdexcept>

uint32_t AmrDeviceMemory::findMemoryType(VkPhysicalDevice physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties) {
	VkPhysicalDeviceMemoryProperties memProperties;
	vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);

	for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
		if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
			return i;
		}
	}

	throw std::runtime_error("failed to find suitable memory type!");
}

AmrDeviceMemory& AmrDeviceMemory::operator=(AmrDeviceMemory&& other)
{
	if (m_deviceMemory != VK_NULL_HANDLE)
		vkFreeMemory(m_device, m_deviceMemory, nullptr);
	m_deviceMemory = other.m_deviceMemory;
	m_device = other.m_device;
	other.m_deviceMemory = VK_NULL_HANDLE;
	return *this;
}


AmrDeviceMemory::AmrDeviceMemory(VkPhysicalDevice physicalDevice, VkDevice device, VkMemoryRequirements memoryRequirements, VkMemoryPropertyFlags memoryPropertyFlags)
	: m_device(device)
{
	VkMemoryAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.allocationSize = memoryRequirements.size;
	allocInfo.memoryTypeIndex = findMemoryType(physicalDevice, memoryRequirements.memoryTypeBits, memoryPropertyFlags);
	if (vkAllocateMemory(device, &allocInfo, nullptr, &m_deviceMemory) != VK_SUCCESS)
		throw std::runtime_error("failed to allocate Vulkan memory!");
}

AmrDeviceMemory::~AmrDeviceMemory()
{
	if (m_deviceMemory != VK_NULL_HANDLE)
		vkFreeMemory(m_device, m_deviceMemory, nullptr);
}

void AmrDeviceMemory::writeData(const void* data, size_t size)
{
	if (data == nullptr)
		throw std::runtime_error("Texture cannot be copied, because source has no data!");
	if (m_deviceMemory == VK_NULL_HANDLE)
		throw std::runtime_error("Texture cannot be copied, because dest is not alloccated!");
	void* bufferPtr;
	vkMapMemory(m_device, m_deviceMemory, 0, static_cast<VkDeviceSize>(size), 0, &bufferPtr);
	memcpy(bufferPtr, data, size);
	vkUnmapMemory(m_device, m_deviceMemory);
}

AmrDeviceMemory::operator VkDeviceMemory() const
{
	return m_deviceMemory;
}
