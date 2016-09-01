#define DEBUG_LAYER

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>



#include <iostream>

#include <vector>
#include <map>
#include <set>
#include <chrono>
#include <array>
#include <functional>
#include <fstream>

#include "AmrDeviceMemory.hpp"
#include "AmrFormat.hpp"

#include "AmrVertex.hpp"


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
#include "AmrSwapChainImageViews.hpp"
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

#include "AmrEngine.hpp"



int main()
{
	AmrEngine* amrEngine = new AmrEngine(800, 600, "Amr Engine");
	delete amrEngine;
	return 0;
}
