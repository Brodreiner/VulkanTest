#pragma once

#include "AmrEngine.hpp"
#include "AmrVertex.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
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
	//// top
	//{ { 0.f, 1.f, 0.f },{ 1.0f, 0.0f, 0.0f },{ 0.0f, 0.0f } },
	//{ { 0.f, 1.f, 1.f },{ 0.0f, 1.0f, 0.0f },{ 0.0f, 1.0f } },
	//{ { 1.f, 1.f, 1.f },{ 0.0f, 0.0f, 1.0f },{ 1.0f, 1.0f } },
	//{ { 1.f, 1.f, 0.f },{ 0.0f, 1.0f, 0.0f },{ 1.0f, 0.0f } },
	//// bottom
	//{ { 0.f, 0.f, 0.f },{ 1.0f, 0.0f, 0.0f },{ 0.0f, 0.0f } },
	//{ { 1.f, 0.f, 0.f },{ 0.0f, 1.0f, 0.0f },{ 1.0f, 0.0f } },
	//{ { 1.f, 0.f, 1.f },{ 0.0f, 0.0f, 1.0f },{ 1.0f, 1.0f } },
	//{ { 0.f, 0.f, 1.f },{ 0.0f, 1.0f, 0.0f },{ 0.0f, 1.0f } },
	//// front
	//{ { 0.f, 1.f, 1.f },{ 1.0f, 0.0f, 0.0f },{ 0.0f, 0.0f } },
	//{ { 0.f, 0.f, 1.f },{ 0.0f, 1.0f, 0.0f },{ 0.0f, 1.0f } },
	//{ { 1.f, 0.f, 1.f },{ 0.0f, 0.0f, 1.0f },{ 1.0f, 1.0f } },
	//{ { 1.f, 1.f, 1.f },{ 0.0f, 1.0f, 0.0f },{ 1.0f, 0.0f } },
	//// back
	//{ { 1.f, 1.f, 0.f },{ 1.0f, 0.0f, 0.0f },{ 0.0f, 0.0f } },
	//{ { 1.f, 0.f, 0.f },{ 0.0f, 1.0f, 0.0f },{ 0.0f, 1.0f } },
	//{ { 0.f, 0.f, 0.f },{ 0.0f, 0.0f, 1.0f },{ 1.0f, 1.0f } },
	//{ { 0.f, 1.f, 0.f },{ 0.0f, 1.0f, 0.0f },{ 1.0f, 0.0f } },
	//// left
	//{ { 0.f, 1.f, 0.f },{ 1.0f, 0.0f, 0.0f },{ 0.0f, 0.0f } },
	//{ { 0.f, 0.f, 0.f },{ 0.0f, 1.0f, 0.0f },{ 0.0f, 1.0f } },
	//{ { 0.f, 0.f, 1.f },{ 0.0f, 0.0f, 1.0f },{ 1.0f, 1.0f } },
	//{ { 0.f, 1.f, 1.f },{ 0.0f, 1.0f, 0.0f },{ 1.0f, 0.0f } },
	//// right
	//{ { 1.f, 1.f, 1.f },{ 1.0f, 0.0f, 0.0f },{ 0.0f, 0.0f } },
	//{ { 1.f, 0.f, 1.f },{ 0.0f, 1.0f, 0.0f },{ 0.0f, 1.0f } },
	//{ { 1.f, 0.f, 0.f },{ 0.0f, 0.0f, 1.0f },{ 1.0f, 1.0f } },
	//{ { 1.f, 1.f, 0.f },{ 0.0f, 1.0f, 0.0f },{ 1.0f, 0.0f } },
};

std::vector<uint32_t> indices = {
	//0, 1, 2, 2, 3, 0, // top
	//4, 5, 6, 6, 7, 4, // bottom
	//8, 9, 10, 10, 11, 8, // front
	//12, 13, 14, 14, 15, 12, // back
	//16, 17, 18, 18, 19, 16, // left
	//20, 21, 22, 22, 23, 20, // right
};


void fillVertexIndexBuffer()
{
	auto chunk = new Chunk;
	chunk->draw(vertices, indices);
	delete chunk;
	//Block block;
	//for (int x = 0; x < 100; ++x)
	//{
	//	for (int y = 0; y < 100; ++y)
	//	{
	//		for (int z = 0; z < 100; ++z)
	//		{
	//			block.drawAllFaces(vertices, indices, glm::vec3{ x,y,z });
	//		}
	//	}
	//}
}

void AmrEngine::doPhysics()
{
	float timeDelta = m_gameTime.getTimeSinceLastCall();
	m_camera.move(timeDelta);
	updateUniformBuffer(timeDelta);

}

AmrEngine::AmrEngine(uint32_t width, uint32_t height, const std::string& title)
{
	fillVertexIndexBuffer();

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

	m_amrTextureImage = AmrTextureImage(m_amrPhysicalDevice, m_amrDevice, m_amrCommandPool, m_amrGraphicsQueue, "textures/dirt.png");
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
		doPhysics();
		drawFrame();
		m_fpsCounter.autoPrint();
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
		switch (key)
		{
		case GLFW_KEY_S:
			m_camera.moveBack(action != GLFW_RELEASE);
			break;
		case GLFW_KEY_W:
			m_camera.moveForward(action != GLFW_RELEASE);
			break;
		case GLFW_KEY_A:
			m_camera.moveLeft(action != GLFW_RELEASE);
			break;
		case GLFW_KEY_D:
			m_camera.moveRight(action != GLFW_RELEASE);
			break;
		}
	});

	m_amrWindow.setMouseMoveCallback([&](double xpos, double ypos)
	{
		std::cout << "Mouse position: " << xpos << " x " << ypos << std::endl;
		m_camera.mouseLook(xpos, ypos);
	});

	m_amrWindow.setMouseClickCallback([&](int button, int action, int mods)
	{
		if (button == GLFW_MOUSE_BUTTON_LEFT)
		{
			if (action == GLFW_PRESS) {
				m_camera.enableMouseLook();
				m_amrWindow.disableCursor();
			}
			if (action == GLFW_RELEASE)
			{
				m_camera.disableMouseLook();
				m_amrWindow.enableCursor();
			}
		}
		std::cout << "Mouse click: button=" << button << " action=" << action << " mods=" << mods << std::endl;
	});

	m_amrWindow.mainLoop();
	vkQueueWaitIdle(m_amrGraphicsQueue);
	std::cout << "Graphics Queue is idle now!" << std::endl;
}

void AmrEngine::updateUniformBuffer(float timeDelta)
{
	static float time = 0;
	time += timeDelta;
	UniformBufferObject ubo = {};

	//ubo.model *= glm::rotate(glm::mat4(), time * glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//ubo.model *= glm::translate(glm::vec3(-0.5f, -0.5f, -0.5f));

	glm::vec3 position = m_camera.getPosition();
	glm::vec3 orientation = m_camera.getOrientation();


	ubo.view = glm::lookAt(position, position + orientation, glm::vec3(0.0f, 1.0f, 0.0f));
	ubo.proj = glm::perspective(glm::radians(45.0f), m_amrSwapChain.getExtent().width / (float)m_amrSwapChain.getExtent().height, 0.1f, 20000.0f);
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
