#pragma once

class AmrCommandBuffer
{
	VkDevice m_device;
	VkCommandPool m_commandPool;
	VkCommandBuffer m_commandBuffer;

public:
	AmrCommandBuffer(VkDevice device, VkCommandPool commandPool, VkCommandBufferLevel commandBufferLevel)
		:m_device(device)
		,m_commandPool(commandPool)
	{
		VkCommandBufferAllocateInfo allocInfo = {};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.level = commandBufferLevel;
		allocInfo.commandPool = commandPool;
		allocInfo.commandBufferCount = 1;
		vkAllocateCommandBuffers(device, &allocInfo, &m_commandBuffer);
	}

	~AmrCommandBuffer()
	{
		vkFreeCommandBuffers(m_device, m_commandPool, 1, &m_commandBuffer);
	}

	void begin(VkCommandBufferUsageFlags flags)
	{
		VkCommandBufferBeginInfo beginInfo = {};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = flags;
		vkBeginCommandBuffer(m_commandBuffer, &beginInfo);
	}

	void end()
	{
		vkEndCommandBuffer(m_commandBuffer);
	}

	void submit(VkQueue queue)
	{
		VkSubmitInfo submitInfo = {};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &m_commandBuffer;
		vkQueueSubmit(queue, 1, &submitInfo, VK_NULL_HANDLE);
	}

	operator VkCommandBuffer() const
	{
		return m_commandBuffer;
	}

};