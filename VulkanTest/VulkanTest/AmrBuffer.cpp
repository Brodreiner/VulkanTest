#pragma once

#include "AmrBuffer.hpp"
#include <algorithm>
#include <stdexcept>

AmrBuffer& AmrBuffer::operator=(AmrBuffer&& other)
{
	if (m_buffer != VK_NULL_HANDLE)
		vkDestroyBuffer(m_device, m_buffer, nullptr);
	m_device = other.m_device;
	m_buffer = other.m_buffer;
	other.m_buffer = VK_NULL_HANDLE;
	return *this;
}

AmrBuffer::AmrBuffer(VkDevice device, VkDeviceSize size, VkBufferUsageFlags usage)
	:m_device(device)
{
	VkBufferCreateInfo bufferInfo = {};
	bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	bufferInfo.size = size;
	bufferInfo.usage = usage;
	bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
	if (vkCreateBuffer(m_device, &bufferInfo, nullptr, &m_buffer) != VK_SUCCESS)
		throw std::runtime_error("failed to create buffer!");
}

AmrBuffer::~AmrBuffer()
{
	if (m_buffer != VK_NULL_HANDLE)
		vkDestroyBuffer(m_device, m_buffer, nullptr);
}

VkMemoryRequirements AmrBuffer::getMemoryRequirements()
{
	VkMemoryRequirements memoryRequirements;
	vkGetBufferMemoryRequirements(m_device, m_buffer, &memoryRequirements);
	return memoryRequirements;
}

AmrBuffer::operator VkBuffer() const
{
	return m_buffer;
}
