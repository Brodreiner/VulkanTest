#pragma once

#include <vulkan/vulkan.h>

#include "AmrBuffer.hpp"
#include "AmrDeviceMemory.hpp"

class AmrCommandPool;

class AmrVertexBuffer
{
	AmrBuffer m_buffer;
	AmrDeviceMemory m_memory;
public:
	AmrVertexBuffer() = default;
	AmrVertexBuffer(const AmrVertexBuffer&) = default;
	AmrVertexBuffer(AmrVertexBuffer&&) = default;
	AmrVertexBuffer& operator=(const AmrVertexBuffer&) = default;
	AmrVertexBuffer& operator=(AmrVertexBuffer&& other) = default;
	~AmrVertexBuffer() = default;

	AmrVertexBuffer(VkPhysicalDevice physicalDevice, VkDevice device, VkQueue queue, const AmrCommandPool& amrCommandPool, void* data, VkDeviceSize size);

	operator VkBuffer() const;
};