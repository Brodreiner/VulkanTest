#pragma once

#include "AmrDescriptorSetLayout.hpp"

#include <array>
#include <stdexcept>

AmrDescriptorSetLayout& AmrDescriptorSetLayout::operator=(AmrDescriptorSetLayout&& other)
{
	if (m_descriptorSetLayout != VK_NULL_HANDLE)
		vkDestroyDescriptorSetLayout(m_device, m_descriptorSetLayout, nullptr);
	m_descriptorSetLayout = other.m_descriptorSetLayout;
	m_device = other.m_device;
	other.m_descriptorSetLayout = VK_NULL_HANDLE;
	return *this;
}


AmrDescriptorSetLayout::AmrDescriptorSetLayout(VkDevice device)
	:m_device(device)
{
	VkDescriptorSetLayoutBinding uboLayoutBinding = {};
	uboLayoutBinding.binding = 0;
	uboLayoutBinding.descriptorCount = 1;
	uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	uboLayoutBinding.pImmutableSamplers = nullptr;
	uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

	VkDescriptorSetLayoutBinding samplerLayoutBinding = {};
	samplerLayoutBinding.binding = 1;
	samplerLayoutBinding.descriptorCount = 1;
	samplerLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	samplerLayoutBinding.pImmutableSamplers = nullptr;
	samplerLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;

	std::array<VkDescriptorSetLayoutBinding, 2> bindings = { uboLayoutBinding, samplerLayoutBinding };
	VkDescriptorSetLayoutCreateInfo layoutInfo = {};
	layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	layoutInfo.bindingCount = static_cast<uint32_t>(bindings.size());
	layoutInfo.pBindings = bindings.data();

	if (vkCreateDescriptorSetLayout(device, &layoutInfo, nullptr, &m_descriptorSetLayout) != VK_SUCCESS) {
		throw std::runtime_error("failed to create descriptor set layout!");
	}
}

AmrDescriptorSetLayout::~AmrDescriptorSetLayout()
{
	if (m_descriptorSetLayout != VK_NULL_HANDLE)
		vkDestroyDescriptorSetLayout(m_device, m_descriptorSetLayout, nullptr);
}

AmrDescriptorSetLayout::operator VkDescriptorSetLayout() const
{
	return m_descriptorSetLayout;
}
