#pragma once

class AmrVertexBuffer
{
	AmrBuffer vertexBuffer;
	AmrDeviceMemory vertexMemory;
public:
	AmrVertexBuffer(VkPhysicalDevice physicalDevice, VkDevice device, VkQueue queue, const AmrCommandPool& amrCommandPool, void* data, VkDeviceSize size)
	{
		AmrBuffer stagingBuffer(device, size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT);
		AmrDeviceMemory stagingMemory(physicalDevice, device, stagingBuffer.getMemoryRequirements(), VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
		stagingMemory.writeData(data, size);
		vkBindBufferMemory(device, stagingBuffer, stagingMemory, 0);

		vertexBuffer = AmrBuffer(device, size, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT);
		vertexMemory = AmrDeviceMemory(physicalDevice, device, vertexBuffer.getMemoryRequirements(), VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
		vkBindBufferMemory(device, vertexBuffer, vertexMemory, 0);

		amrCommandPool.copyBuffer(queue, stagingBuffer, vertexBuffer, size);
	}
};