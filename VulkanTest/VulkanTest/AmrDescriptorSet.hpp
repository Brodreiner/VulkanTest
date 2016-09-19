#pragma once

#include <vulkan/vulkan.h>

class AmrUniformBuffer;

class AmrDescriptorSet
{
	VkDevice m_device = VK_NULL_HANDLE;
	VkDescriptorPool m_descriptorPool = VK_NULL_HANDLE;
	VkDescriptorSet m_descriptorSet = VK_NULL_HANDLE;
public:
	AmrDescriptorSet() = default;
	AmrDescriptorSet(const AmrDescriptorSet&) = delete;
	AmrDescriptorSet(AmrDescriptorSet&&) = delete;
	AmrDescriptorSet& operator=(const AmrDescriptorSet&) = delete;
	AmrDescriptorSet& operator=(AmrDescriptorSet&& other) = default;
	~AmrDescriptorSet() = default;

	AmrDescriptorSet(VkDevice device, VkDescriptorSetLayout descriptorSetLayout, VkDescriptorPool descriptorPool, const AmrUniformBuffer& amrUniformBuffer, VkImageView textureImageView, VkSampler textureSampler);


	operator VkDescriptorSet() const;
};
