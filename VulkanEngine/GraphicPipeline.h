#pragma once

#include "Utilities.h"
#include "RenderPassHandler.h"
#include "SwapChainHandler.h"

class GraphicPipeline
{
public:
	GraphicPipeline();
	GraphicPipeline(MainDevice &mainDevice, SwapChainHandler& swapChainHandler, RenderPassHandler& renderPass, VkDescriptorSetLayout& descriptorSetLayout,
		TextureObjects& textureObjects, VkPushConstantRange& pushCostantRange);

	VkPipeline&		  GetPipeline()   { return m_GraphicsPipeline; }
	VkPipelineLayout& GetLayout()	  { return m_PipelineLayout; }

	VkShaderModule CreateShaderModules(const char* path);
	VkPipelineShaderStageCreateInfo CreateVertexShaderStage();
	VkPipelineShaderStageCreateInfo CreateFragmentShaderStage();
	void CreateShaderStages();
	void CreateGraphicPipeline();
	
	void DestroyShaderModules();
	void DestroyPipeline();

private:
	MainDevice			  m_MainDevice;
	SwapChainHandler	  m_SwapChainHandler;
	RenderPassHandler	  m_RenderPassHandler;
	VkDescriptorSetLayout m_DescriptorSetLayout;
	TextureObjects		  m_TextureObjects;
	VkPushConstantRange   m_PushCostantRange;

	const char* m_VertexShaderSPIRVPath = "./Shaders/vert.spv";
	const char* m_FragmentShaderSPIRVPath = "./Shaders/frag.spv";

private:
	VkPipeline		  m_GraphicsPipeline;
	VkPipelineLayout  m_PipelineLayout;
	VkPipelineShaderStageCreateInfo m_ShaderStages[2];

	VkShaderModule m_VertexShaderModule;
	VkShaderModule m_FragmentShaderModule;
};