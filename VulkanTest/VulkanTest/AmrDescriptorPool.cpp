#pragma once

#include "AmrDescriptorPool.hpp"

#include <array>


AmrDescriptorPool::AmrDescriptorPool(VkDevice device)
	:m_device(device)
{
	std::array<VkDescriptorPoolSize, 2> poolSizes = {};
	poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	poolSizes[0].descriptorCount = 1;
	poolSizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	poolSizes[1].descriptorCount = 1;

	VkDescriptorPoolCreateInfo poolInfo = {};
	poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	poolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
	poolInfo.pPoolSizes = poolSizes.data();
	poolInfo.maxSets = 1;

	if (vkCreateDescriptorPool(device, &poolInfo, nullptr, &m_descriptorPool) != VK_SUCCESS)
		throw std::runtime_error("failed to create descriptor pool!");
}

AmrDescriptorPool::~AmrDescriptorPool()
{
	if (m_descriptorPool != VK_NULL_HANDLE)
		vkDestroyDescriptorPool(m_device, m_descriptorPool, nullptr);
}

AmrDescriptorPool::operator VkDescriptorPool() const
{
	return m_descriptorPool;
}
