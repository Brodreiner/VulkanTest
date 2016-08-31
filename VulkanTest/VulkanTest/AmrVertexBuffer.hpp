#pragma once

class AmrVertexBuffer
{
	AmrBuffer m_buffer;
	AmrDeviceMemory m_memory;
public:
	AmrVertexBuffer(VkPhysicalDevice physicalDevice, VkDevice device, VkQueue queue, const AmrCommandPool& amrCommandPool, void* data, VkDeviceSize size)
	{
		AmrBuffer stagingBuffer(device, size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT);
		AmrDeviceMemory stagingMemory(physicalDevice, device, stagingBuffer.getMemoryRequirements(), VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
		stagingMemory.writeData(data, size);
		vkBindBufferMemory(device, stagingBuffer, stagingMemory, 0);

		m_buffer = AmrBuffer(device, size, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT);
		m_memory = AmrDeviceMemory(physicalDevice, device, m_buffer.getMemoryRequirements(), VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
		vkBindBufferMemory(device, m_buffer, m_memory, 0);

		amrCommandPool.copyBuffer(queue, stagingBuffer, m_buffer, size);
	}

	operator VkBuffer() const
	{
		return m_buffer;
	}
};