#pragma once

class AmrUniformBuffer
{
	AmrBuffer amrStagingBuffer;
	AmrBuffer amrGpuBuffer;
	AmrDeviceMemory amrStagingMemory;
	AmrDeviceMemory amrGpuMemory;

public:
	AmrUniformBuffer(VkPhysicalDevice physicalDevice, VkDevice device, VkDeviceSize size)
		: amrStagingBuffer(device, size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT)
		, amrStagingMemory(physicalDevice, device, amrStagingBuffer.getMemoryRequirements(), VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)
		, amrGpuBuffer(device, size, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT)
		, amrGpuMemory(physicalDevice, device, amrGpuBuffer.getMemoryRequirements(), VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)
	{
	}

};