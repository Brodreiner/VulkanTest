#pragma once

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


class AmrEngine
{
	AmrWindow m_amrWindow;
	AmrInstance m_amrInstance;
	AmrDebugCallback m_amrDebugCallback;
	AmrSurface m_amrSurface;
	AmrPhysicalDevice m_amrPhysicalDevice;
	AmrQueueFamily m_amrQueueFamily;
	AmrDevice m_amrDevice;
	AmrQueue m_amrGraphicsQueue;
	AmrQueue m_amrPresentQueue;
	AmrSwapChain m_amrSwapChain;
	AmrRenderPass m_amrRenderPass;
	AmrDescriptorSetLayout m_amrDescriptorSetLayout;
	AmrPipelineLayout m_amrPipelineLayout;
	AmrPipeline m_amrPipeline;
	AmrCommandPool m_amrCommandPool;
	AmrDepthImage m_amrDepthImage;
	AmrFramebufferStack m_amrFramebufferStack;
	AmrTextureImage m_amrTextureImage;
	AmrImageView m_amrTextureImageView;
	AmrTextureSampler m_amrTextureSampler;
	AmrVertexBuffer m_amrVertexBuffer;
	AmrIndexBuffer m_amrIndexBuffer;
	AmrUniformBuffer m_amrUniformBuffer;
	AmrDescriptorPool m_amrDescriptorPool;

public:
	AmrEngine(uint32_t width, uint32_t height, const std::string& title)
		: m_amrWindow(width, height, title)
		, m_amrDebugCallback(m_amrInstance)
		, m_amrSurface(m_amrWindow, m_amrInstance)
		, m_amrPhysicalDevice(m_amrInstance, m_amrSurface)
		, m_amrQueueFamily(m_amrPhysicalDevice, m_amrSurface)
		, m_amrDevice(m_amrPhysicalDevice, m_amrQueueFamily.getDeviceQueueCreateInfoSize(), m_amrQueueFamily.getDeviceQueueCreateInfoData())
		, m_amrGraphicsQueue(m_amrDevice, m_amrQueueFamily.getGraphicsQueueFamilyIndex(), 0)
		, m_amrPresentQueue(m_amrDevice, m_amrQueueFamily.getPresentQueueFamilyIndex(), 0)
		, m_amrSwapChain(m_amrPhysicalDevice, m_amrDevice, m_amrSurface, m_amrQueueFamily.getGraphicsQueueFamilyIndex(), m_amrQueueFamily.getPresentQueueFamilyIndex(), { width, height })
		, m_amrRenderPass(m_amrPhysicalDevice, m_amrDevice, m_amrSwapChain.getImageFormat())
		, m_amrDescriptorSetLayout(m_amrDevice)
		, m_amrPipelineLayout(m_amrDevice, m_amrDescriptorSetLayout)
		, m_amrPipeline(m_amrDevice, m_amrSwapChain.getExtent(), m_amrPipelineLayout, m_amrRenderPass)
		, m_amrCommandPool(m_amrDevice, m_amrQueueFamily.getGraphicsQueueFamilyIndex())
		, m_amrDepthImage(m_amrPhysicalDevice, m_amrGraphicsQueue, m_amrCommandPool, m_amrDevice, m_amrSwapChain.getExtent())
		, m_amrFramebufferStack(m_amrDevice, m_amrSwapChain.getImageViews(), m_amrDepthImage.getImageView(), m_amrRenderPass, m_amrSwapChain.getExtent())
		, m_amrTextureImage(m_amrPhysicalDevice, m_amrDevice, m_amrCommandPool, m_amrGraphicsQueue, "textures/texture.jpg")
		, m_amrTextureImageView(m_amrDevice, m_amrTextureImage, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_ASPECT_COLOR_BIT)
		, m_amrTextureSampler(m_amrDevice)
		, m_amrVertexBuffer(m_amrPhysicalDevice, m_amrDevice, m_amrGraphicsQueue, m_amrCommandPool, &(vertices[0]), sizeof(vertices[0]) * vertices.size())
		, m_amrIndexBuffer(m_amrPhysicalDevice, m_amrDevice, m_amrGraphicsQueue, m_amrCommandPool, &(indices[0]), sizeof(indices[0]) * indices.size())
		, m_amrUniformBuffer(m_amrPhysicalDevice, m_amrDevice, sizeof(UniformBufferObject))
		, m_amrDescriptorPool (m_amrDevice)

	{
		m_amrWindow.setEventLoopCallback([&]() {
		});
		m_amrWindow.mainLoop();
		vkQueueWaitIdle(m_amrGraphicsQueue);
		std::cout << "Graphics Queue is idle now!" << std::endl;
	}

};