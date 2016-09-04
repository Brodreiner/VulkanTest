#pragma once

#include "AmrUniformBuffer.hpp"

AmrUniformBuffer::AmrUniformBuffer(VkPhysicalDevice physicalDevice, VkDevice device, VkDeviceSize size)
	: m_amrStagingBuffer(device, size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT)
	, m_amrStagingMemory(physicalDevice, device, m_amrStagingBuffer.getMemoryRequirements(), VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)
	, m_amrGpuBuffer(device, size, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT)
	, m_amrGpuMemory(physicalDevice, device, m_amrGpuBuffer.getMemoryRequirements(), VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)
	, m_size(size)
{
	vkBindBufferMemory(device, m_amrStagingBuffer, m_amrStagingMemory, 0);
	vkBindBufferMemory(device, m_amrGpuBuffer, m_amrGpuMemory, 0);
}

VkBuffer AmrUniformBuffer::getGpuBuffer() const
{
	return m_amrGpuBuffer;
}

VkDeviceSize AmrUniformBuffer::getDeviceSize() const
{
	return m_size;
}

AmrDeviceMemory& AmrUniformBuffer::getStagingMemory()
{
	return m_amrStagingMemory;
}

AmrBuffer& AmrUniformBuffer::getStagingBuffer()
{
	return m_amrStagingBuffer;
}

AmrBuffer& AmrUniformBuffer::getGpuBuffer()
{
	return m_amrGpuBuffer;
}
