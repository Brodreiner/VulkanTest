#pragma once

#include "AmrPipelineLayout.hpp"
#include <stdexcept>

AmrPipelineLayout::AmrPipelineLayout(VkDevice device, VkDescriptorSetLayout descriptorSetLayout)
	:m_device(device)
{
	VkDescriptorSetLayout setLayouts[] = { descriptorSetLayout };
	VkPipelineLayoutCreateInfo pipelineLayoutInfo = {};
	pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipelineLayoutInfo.setLayoutCount = 1;
	pipelineLayoutInfo.pSetLayouts = setLayouts;

	if (vkCreatePipelineLayout(m_device, &pipelineLayoutInfo, nullptr, &m_pipelineLayout) != VK_SUCCESS) {
		throw std::runtime_error("failed to create pipeline layout!");
	}

}

AmrPipelineLayout::~AmrPipelineLayout()
{
	if (m_pipelineLayout != VK_NULL_HANDLE)
		vkDestroyPipelineLayout(m_device, m_pipelineLayout, nullptr);
}

AmrPipelineLayout::operator VkPipelineLayout() const
{
	return m_pipelineLayout;
}
