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

#include "AmrFormat.hpp"

#include "AmrVertex.hpp"
#include "AmrFramebuffer.hpp"
#include "AmrFramebufferStack.hpp"
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



#include "AmrEngine.hpp"



int main()
{
	AmrEngine amrEngine(800, 600, "Amr Engine");
	return 0;
}
