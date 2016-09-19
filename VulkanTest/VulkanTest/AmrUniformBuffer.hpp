#pragma once

#include <vulkan/vulkan.h>

#include "AmrBuffer.hpp"
#include "AmrDeviceMemory.hpp"

class AmrUniformBuffer
{
	AmrBuffer m_amrStagingBuffer;
	AmrBuffer m_amrGpuBuffer;
	AmrDeviceMemory m_amrStagingMemory;
	AmrDeviceMemory m_amrGpuMemory;
	VkDeviceSize m_size = 0;

public:
	AmrUniformBuffer() = default;
	AmrUniformBuffer(const AmrUniformBuffer&) = default;
	AmrUniformBuffer(AmrUniformBuffer&&) = default;
	AmrUniformBuffer& operator=(const AmrUniformBuffer&) = default;
	AmrUniformBuffer& operator=(AmrUniformBuffer&& other) = default;
	~AmrUniformBuffer() = default;

	AmrUniformBuffer(VkPhysicalDevice physicalDevice, VkDevice device, VkDeviceSize size);

	VkBuffer getGpuBuffer() const;

	VkDeviceSize getDeviceSize() const;

	AmrDeviceMemory& getStagingMemory();

	AmrBuffer& getStagingBuffer();

	AmrBuffer& getGpuBuffer();

};