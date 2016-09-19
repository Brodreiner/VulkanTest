#pragma once

#include "AmrTextureSampler.hpp"
#include <stdexcept>

AmrTextureSampler& AmrTextureSampler::operator=(AmrTextureSampler&& other)
{
	if (m_sampler != VK_NULL_HANDLE)
		vkDestroySampler(m_device, m_sampler, nullptr);
	m_device = other.m_device;
	m_sampler = other.m_sampler;
	other.m_sampler = VK_NULL_HANDLE;
	return *this;
}

AmrTextureSampler::AmrTextureSampler(VkDevice device)
	:m_device(device)
{
	VkSamplerCreateInfo samplerInfo = {};
	samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
	samplerInfo.magFilter = VK_FILTER_LINEAR;
	samplerInfo.minFilter = VK_FILTER_LINEAR;
	samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
	samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
	samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
	samplerInfo.anisotropyEnable = VK_TRUE;
	samplerInfo.maxAnisotropy = 16;
	samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
	samplerInfo.unnormalizedCoordinates = VK_FALSE;
	samplerInfo.compareEnable = VK_FALSE;
	samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;
	samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
	if (vkCreateSampler(m_device, &samplerInfo, nullptr, &m_sampler) != VK_SUCCESS)
		throw std::runtime_error("failed to create texture sampler!");
}

AmrTextureSampler::~AmrTextureSampler()
{
	if (m_sampler != VK_NULL_HANDLE)
		vkDestroySampler(m_device, m_sampler, nullptr);
}

AmrTextureSampler::operator VkSampler() const
{
	return m_sampler;
}

