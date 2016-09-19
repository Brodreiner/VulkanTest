#pragma once

#include "AmrCommandBuffer.hpp"
#include <algorithm>

AmrCommandBuffer& AmrCommandBuffer::operator=(AmrCommandBuffer&& other)
{
	if (m_commandBuffer != VK_NULL_HANDLE)
		vkFreeCommandBuffers(m_device, m_commandPool, 1, &m_commandBuffer);
	m_commandBuffer = other.m_commandBuffer;
	m_commandPool = other.m_commandPool;
	m_device = other.m_device;
	other.m_commandBuffer = VK_NULL_HANDLE;
	return *this;
}

AmrCommandBuffer::AmrCommandBuffer(VkDevice device, VkCommandPool commandPool, VkCommandBufferLevel commandBufferLevel)
	:m_device(device)
	, m_commandPool(commandPool)
{
	VkCommandBufferAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.level = commandBufferLevel;
	allocInfo.commandPool = commandPool;
	allocInfo.commandBufferCount = 1;
	vkAllocateCommandBuffers(device, &allocInfo, &m_commandBuffer);
}

AmrCommandBuffer::~AmrCommandBuffer()
{
	if(m_commandBuffer != VK_NULL_HANDLE)
		vkFreeCommandBuffers(m_device, m_commandPool, 1, &m_commandBuffer);
}

void AmrCommandBuffer::begin(VkCommandBufferUsageFlags flags)
{
	VkCommandBufferBeginInfo beginInfo = {};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = flags;
	vkBeginCommandBuffer(m_commandBuffer, &beginInfo);
}

void AmrCommandBuffer::end()
{
	vkEndCommandBuffer(m_commandBuffer);
}

void AmrCommandBuffer::submit(VkQueue queue)
{
	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &m_commandBuffer;
	vkQueueSubmit(queue, 1, &submitInfo, VK_NULL_HANDLE);
}

AmrCommandBuffer::operator VkCommandBuffer() const
{
	return m_commandBuffer;
}

