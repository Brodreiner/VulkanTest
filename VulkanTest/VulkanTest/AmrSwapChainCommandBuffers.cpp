#pragma once

#include "AmrSwapChainCommandBuffers.hpp"
#include <stdexcept>
#include <array>
#include "AmrFramebuffer.hpp"

AmrSwapChainCommandBuffers& AmrSwapChainCommandBuffers::operator=(AmrSwapChainCommandBuffers&& other)
{
	if (m_commandBuffers.size() > 0)
		vkFreeCommandBuffers(m_device, m_commandPool, static_cast<uint32_t>(m_commandBuffers.size()), m_commandBuffers.data());
	m_commandBuffers = std::move(other.m_commandBuffers);
	m_commandPool = other.m_commandPool;
	m_device = other.m_device;
	other.m_commandBuffers.clear();
	return *this;
}

AmrSwapChainCommandBuffers::AmrSwapChainCommandBuffers(VkDevice device, VkCommandPool commandPool, VkPipeline graphicsPipeline, VkBuffer vertexBuffer, VkBuffer indexBuffer, uint32_t indexCount, VkPipelineLayout pipelineLayout, VkDescriptorSet descriptorSet, const AmrFramebufferStack& amrFramebufferStack)
	: m_device(device)
	, m_commandPool(commandPool)
{
	m_commandBuffers.resize(amrFramebufferStack.size());

	VkCommandBufferAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = commandPool;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = (uint32_t)m_commandBuffers.size();

	if (vkAllocateCommandBuffers(device, &allocInfo, m_commandBuffers.data()) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate command buffers!");
	}

	for (size_t i = 0; i < m_commandBuffers.size(); i++) {
		VkCommandBufferBeginInfo beginInfo = {};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;

		vkBeginCommandBuffer(m_commandBuffers[i], &beginInfo);

		VkRenderPassBeginInfo renderPassInfo = {};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo.renderPass = amrFramebufferStack.getRenderPass();
		renderPassInfo.framebuffer = amrFramebufferStack[i];
		renderPassInfo.renderArea.offset = { 0, 0 };
		renderPassInfo.renderArea.extent = amrFramebufferStack.getExtent();

		std::array<VkClearValue, 2> clearValues = {};
		clearValues[0].color = { 0.0f, 0.0f, 0.0f, 1.0f };
		clearValues[1].depthStencil = { 1.0f, 0 };

		renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
		renderPassInfo.pClearValues = clearValues.data();

		vkCmdBeginRenderPass(m_commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

		vkCmdBindPipeline(m_commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);

		VkBuffer vertexBuffers[] = { vertexBuffer };
		VkDeviceSize offsets[] = { 0 };
		vkCmdBindVertexBuffers(m_commandBuffers[i], 0, 1, vertexBuffers, offsets);

		vkCmdBindIndexBuffer(m_commandBuffers[i], indexBuffer, 0, VK_INDEX_TYPE_UINT32);

		vkCmdBindDescriptorSets(m_commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, 1, &descriptorSet, 0, nullptr);

		vkCmdDrawIndexed(m_commandBuffers[i], indexCount, 1, 0, 0, 0);

		vkCmdEndRenderPass(m_commandBuffers[i]);

		if (vkEndCommandBuffer(m_commandBuffers[i]) != VK_SUCCESS)
			throw std::runtime_error("failed to record command buffer!");
	}
}

AmrSwapChainCommandBuffers::~AmrSwapChainCommandBuffers()
{
	if (m_commandBuffers.size() > 0)
		vkFreeCommandBuffers(m_device, m_commandPool, static_cast<uint32_t>(m_commandBuffers.size()), m_commandBuffers.data());
}

VkCommandBuffer& AmrSwapChainCommandBuffers::operator[](size_t i)
{
	return m_commandBuffers[i];
}

