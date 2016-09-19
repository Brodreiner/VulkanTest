#pragma once

#include "AmrEngine.hpp"
#include "AmrVertex.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <GLFW/glfw3.h>

#include <iostream>
#include <chrono>

struct UniformBufferObject {
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 proj;
};

std::vector<AmrVertex> vertices = {
	{ { -0.5f, -0.5f, 0.0f },{ 1.0f, 0.0f, 0.0f },{ 0.0f, 0.0f } },
	{ { 0.5f, -0.5f, 0.0f },{ 0.0f, 1.0f, 0.0f },{ 1.0f, 0.0f } },
	{ { 0.5f, 0.5f, 0.0f },{ 0.0f, 0.0f, 1.0f },{ 1.0f, 1.0f } },
	{ { -0.5f, 0.5f, 0.0f },{ 1.0f, 1.0f, 1.0f },{ 0.0f, 1.0f } },

	{ { -0.5f, -0.5f, -0.5f },{ 1.0f, 0.0f, 0.0f },{ 0.0f, 0.0f } },
	{ { 0.5f, -0.5f, -0.5f },{ 0.0f, 1.0f, 0.0f },{ 1.0f, 0.0f } },
	{ { 0.5f, 0.5f, -0.5f },{ 0.0f, 0.0f, 1.0f },{ 1.0f, 1.0f } },
	{ { -0.5f, 0.5f, -0.5f },{ 1.0f, 1.0f, 1.0f },{ 0.0f, 1.0f } }
};

std::vector<uint32_t> indices = {
	0, 1, 2, 2, 3, 0,
	4, 5, 6, 6, 7, 4
};


AmrEngine::AmrEngine(uint32_t width, uint32_t height, const std::string& title)
{
	m_amrWindow = AmrWindow(width, height, title);
	m_amrInstance = AmrInstance("Vulkan Test");
	m_amrDebugCallback = AmrDebugCallback(m_amrInstance);
	m_amrSurface = AmrSurface(m_amrWindow, m_amrInstance);
	m_amrPhysicalDevice = AmrPhysicalDevice(m_amrInstance, m_amrSurface);
	m_amrQueueFamily = AmrQueueFamily(m_amrPhysicalDevice, m_amrSurface);
	m_amrDevice = AmrDevice(m_amrPhysicalDevice, m_amrQueueFamily.getDeviceQueueCreateInfoSize(), m_amrQueueFamily.getDeviceQueueCreateInfoData());
	m_amrGraphicsQueue = AmrQueue(m_amrDevice, m_amrQueueFamily.getGraphicsQueueFamilyIndex(), 0);
	m_amrPresentQueue = AmrQueue(m_amrDevice, m_amrQueueFamily.getPresentQueueFamilyIndex(), 0);
	m_amrCommandPool = AmrCommandPool(m_amrDevice, m_amrQueueFamily.getGraphicsQueueFamilyIndex());

	m_amrTextureImage = AmrTextureImage(m_amrPhysicalDevice, m_amrDevice, m_amrCommandPool, m_amrGraphicsQueue, "textures/texture.jpg");
	m_amrTextureImageView = AmrImageView(m_amrDevice, m_amrTextureImage, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_ASPECT_COLOR_BIT);
	m_amrTextureSampler = AmrTextureSampler(m_amrDevice);
	m_amrVertexBuffer = AmrVertexBuffer(m_amrPhysicalDevice, m_amrDevice, m_amrGraphicsQueue, m_amrCommandPool, &(vertices[0]), sizeof(vertices[0]) * vertices.size());
	m_amrIndexBuffer = AmrIndexBuffer(m_amrPhysicalDevice, m_amrDevice, m_amrGraphicsQueue, m_amrCommandPool, &(indices[0]), sizeof(indices[0]) * indices.size());
	m_amrUniformBuffer = AmrUniformBuffer(m_amrPhysicalDevice, m_amrDevice, sizeof(UniformBufferObject));
	m_amrDescriptorSetLayout = AmrDescriptorSetLayout(m_amrDevice);
	m_amrDescriptorPool = AmrDescriptorPool(m_amrDevice);
	m_amrDescriptorSet = AmrDescriptorSet(m_amrDevice, m_amrDescriptorSetLayout, m_amrDescriptorPool, m_amrUniformBuffer, m_amrTextureImageView, m_amrTextureSampler);
	m_amrImageAvailableSemaphore = AmrSemaphore(m_amrDevice);
	m_amrRenderFinishedSemaphore = AmrSemaphore(m_amrDevice);

	recreateSwapChain();

	m_amrWindow.setEventLoopCallback([&]() {
		updateUniformBuffer();
		drawFrame();
	});

	m_amrWindow.setResizeCallback([&](int width, int height) {
		recreateSwapChain();
	});

	m_amrWindow.setKeyCallback([&](int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_E && action == GLFW_PRESS)
			std::cout << "E has been pressed!" << std::endl;
		if (key == GLFW_KEY_E && action == GLFW_RELEASE)
			std::cout << "E has been released!" << std::endl;
	});

	m_amrWindow.setMouseMoveCallback([&](double xpos, double ypos)
	{
		std::cout << "Mouse position: " << xpos << " x " << ypos << std::endl;
	});

	m_amrWindow.setMouseClickCallback([&](int button, int action, int mods)
	{
		if (button == GLFW_MOUSE_BUTTON_LEFT)
		{
			if(action == GLFW_PRESS)
				m_amrWindow.disableCursor();
			if (action == GLFW_RELEASE)
				m_amrWindow.enableCursor();
		}
		std::cout << "Mouse click: button=" << button << " action=" << action << " mods=" << mods << std::endl;
	});

	m_amrWindow.mainLoop();
	vkQueueWaitIdle(m_amrGraphicsQueue);
	std::cout << "Graphics Queue is idle now!" << std::endl;
}

void AmrEngine::updateUniformBuffer()
{
	static auto startTime = std::chrono::high_resolution_clock::now();

	auto currentTime = std::chrono::high_resolution_clock::now();
	float time = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count() / 1000.0f;

	UniformBufferObject ubo = {};
	ubo.model = glm::rotate(glm::mat4(), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	ubo.proj = glm::perspective(glm::radians(45.0f), m_amrSwapChain.getExtent().width / (float)m_amrSwapChain.getExtent().height, 0.1f, 10.0f);
	ubo.proj[1][1] *= -1;

	m_amrUniformBuffer.getStagingMemory().writeData(&ubo, sizeof(ubo));
	m_amrCommandPool.copyBuffer(m_amrGraphicsQueue, m_amrUniformBuffer.getStagingBuffer(), m_amrUniformBuffer.getGpuBuffer(), sizeof(ubo));
}

void AmrEngine::recreateSwapChain()
{
	vkDeviceWaitIdle(m_amrDevice);
	m_amrSwapChain = AmrSwapChain(m_amrPhysicalDevice, m_amrDevice, m_amrSurface, m_amrQueueFamily.getGraphicsQueueFamilyIndex(), m_amrQueueFamily.getPresentQueueFamilyIndex(), m_amrSwapChain);
	m_amrRenderPass = AmrRenderPass(m_amrPhysicalDevice, m_amrDevice, m_amrSwapChain.getImageFormat());
	m_amrPipelineLayout = AmrPipelineLayout(m_amrDevice, m_amrDescriptorSetLayout);
	m_amrPipeline = AmrPipeline(m_amrDevice, m_amrSwapChain.getExtent(), m_amrPipelineLayout, m_amrRenderPass);
	m_amrDepthImage = AmrDepthImage(m_amrPhysicalDevice, m_amrGraphicsQueue, m_amrCommandPool, m_amrDevice, m_amrSwapChain.getExtent());
	m_amrFramebufferStack = AmrFramebufferStack(m_amrDevice, m_amrSwapChain.getImageViews(), m_amrDepthImage.getImageView(), m_amrRenderPass, m_amrSwapChain.getExtent());
	m_amrSwapChainCommandBuffers = AmrSwapChainCommandBuffers(m_amrDevice, m_amrCommandPool, m_amrPipeline, m_amrVertexBuffer, m_amrIndexBuffer, static_cast<uint32_t>(indices.size()), m_amrPipelineLayout, m_amrDescriptorSet, m_amrFramebufferStack);
}

void AmrEngine::drawFrame()
{
	uint32_t imageIndex;
	VkResult result = vkAcquireNextImageKHR(m_amrDevice, m_amrSwapChain, std::numeric_limits<uint64_t>::max(), m_amrImageAvailableSemaphore, VK_NULL_HANDLE, &imageIndex);

	if (result == VK_ERROR_OUT_OF_DATE_KHR) {
		recreateSwapChain();
		return;
	}
	else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
		throw std::runtime_error("failed to acquire swap chain image!");
	}

	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

	VkSemaphore waitSemaphores[] = { m_amrImageAvailableSemaphore };
	VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = waitSemaphores;
	submitInfo.pWaitDstStageMask = waitStages;

	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &m_amrSwapChainCommandBuffers[imageIndex];

	VkSemaphore signalSemaphores[] = { m_amrRenderFinishedSemaphore };
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = signalSemaphores;

	if (vkQueueSubmit(m_amrGraphicsQueue, 1, &submitInfo, VK_NULL_HANDLE) != VK_SUCCESS) {
		throw std::runtime_error("failed to submit draw command buffer!");
	}

	VkPresentInfoKHR presentInfo = {};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = signalSemaphores;

	VkSwapchainKHR swapChains[] = { m_amrSwapChain };
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = swapChains;

	presentInfo.pImageIndices = &imageIndex;

	result = vkQueuePresentKHR(m_amrPresentQueue, &presentInfo);

	if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR) {
		recreateSwapChain();
	}
	else if (result != VK_SUCCESS) {
		throw std::runtime_error("failed to present swap chain image!");
	}
}
