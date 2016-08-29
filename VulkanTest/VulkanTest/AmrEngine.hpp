#pragma once

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
	AmrFormat m_amrDepthFormat;
	AmrImage m_amrDepthImage;
	AmrImageView m_amrDepthImageView;
	AmrFramebufferStack m_amrFramebufferStack;
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
		, m_amrDepthFormat(m_amrPhysicalDevice, { VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT }, VK_IMAGE_TILING_OPTIMAL, VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)
		, m_amrDepthImage(m_amrPhysicalDevice, m_amrDevice, m_amrSwapChain.getExtent(), m_amrDepthFormat, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)
		, m_amrDepthImageView(m_amrDevice, m_amrDepthImage, m_amrDepthFormat, VK_IMAGE_ASPECT_DEPTH_BIT)
		, m_amrFramebufferStack(m_amrDevice, m_amrSwapChain.getImageViews(), m_amrDepthImageView, m_amrRenderPass, m_amrSwapChain.getExtent())

	{
		m_amrWindow.mainLoop();
	}

};