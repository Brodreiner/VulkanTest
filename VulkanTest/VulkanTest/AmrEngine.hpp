#pragma once

#include <vulkan/vulkan.h>

#include "AmrBuffer.hpp"
#include "AmrFramebuffer.hpp"
#include "AmrFramebufferStack.hpp"
#include "AmrCommandBuffer.hpp"
#include "AmrWindow.hpp"
#include "AmrValidationLayer.hpp"
#include "AmrDebugCallback.hpp"
#include "AmrSurface.hpp"
#include "AmrQueueFamily.hpp"
#include "AmrQueue.hpp"
#include "AmrPhysicalDevice.hpp"
#include "AmrDevice.hpp"
#include "AmrImageView.hpp"
#include "AmrSwapChain.hpp"
#include "AmrInstance.hpp"
#include "AmrRenderPass.hpp"
#include "AmrDescriptorSetLayout.hpp"
#include "AmrShader.hpp"
#include "AmrPipelineLayout.hpp"
#include "AmrPipeline.hpp"
#include "AmrCommandPool.hpp"
#include "AmrImage.hpp"
#include "AmrTextureFile.hpp"
#include "AmrTextureImage.hpp"
#include "AmrTextureSampler.hpp"
#include "AmrDepthImage.hpp"
#include "AmrVertexBuffer.hpp"
#include "AmrIndexBuffer.hpp"
#include "AmrUniformBuffer.hpp"
#include "AmrDescriptorPool.hpp"
#include "AmrDescriptorSet.hpp"
#include "AmrSwapChainCommandBuffers.hpp"
#include "AmrSemaphore.hpp"

#include "GameTime.hpp"
#include "Camera.hpp"
#include "Block.hpp"
#include "Chunk.hpp"
#include "FpsCounter.hpp"

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
	AmrCommandPool m_amrCommandPool;
	AmrSwapChain m_amrSwapChain;
	AmrRenderPass m_amrRenderPass;
	AmrDescriptorSetLayout m_amrDescriptorSetLayout;
	AmrPipelineLayout m_amrPipelineLayout;
	AmrPipeline m_amrPipeline;
	AmrDepthImage m_amrDepthImage;
	AmrFramebufferStack m_amrFramebufferStack;
	AmrTextureImage m_amrTextureImage;
	AmrImageView m_amrTextureImageView;
	AmrTextureSampler m_amrTextureSampler;
	AmrVertexBuffer m_amrVertexBuffer;
	AmrIndexBuffer m_amrIndexBuffer;
	AmrUniformBuffer m_amrUniformBuffer;
	AmrDescriptorPool m_amrDescriptorPool;
	AmrDescriptorSet m_amrDescriptorSet;
	AmrSwapChainCommandBuffers m_amrSwapChainCommandBuffers;
	AmrSemaphore m_amrImageAvailableSemaphore;
	AmrSemaphore m_amrRenderFinishedSemaphore;

	GameTime m_gameTime;
	Camera m_camera;
	FpsCounter m_fpsCounter;

	void doPhysics();
public:
	AmrEngine(uint32_t width, uint32_t height, const std::string& title);

	void updateUniformBuffer(float timeDelta);

	void recreateSwapChain();

	void drawFrame();
};