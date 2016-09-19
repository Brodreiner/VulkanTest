#pragma once

#include <vulkan/vulkan.h>
#include "AmrBuffer.hpp"
#include "AmrDeviceMemory.hpp"

class AmrCommandPool;

class AmrIndexBuffer
{
	AmrBuffer m_buffer;
	AmrDeviceMemory m_memory;
public:
	AmrIndexBuffer() = default;
	AmrIndexBuffer(const AmrIndexBuffer&) = default;
	AmrIndexBuffer(AmrIndexBuffer&&);
	AmrIndexBuffer& operator=(const AmrIndexBuffer&) = default;
	AmrIndexBuffer& operator=(AmrIndexBuffer&& other) = default;
	~AmrIndexBuffer() = default;

	AmrIndexBuffer(VkPhysicalDevice physicalDevice, VkDevice device, VkQueue queue, const AmrCommandPool& amrCommandPool, void* data, VkDeviceSize size);

	operator VkBuffer() const;
};