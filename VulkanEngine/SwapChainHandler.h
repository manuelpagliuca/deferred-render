#pragma once

#include "pch.h"

#include "Window.h"
#include "Utilities.h"

struct SwapChainImage {
	VkImage image;
	VkImageView imageView;
};

struct SwapChainDetails {
	VkSurfaceCapabilitiesKHR surfaceCapabilities = {};
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentationModes;
};

class SwapChain
{
public:
	SwapChain();
	SwapChain(MainDevice *main_device, VkSurfaceKHR *surface, 
		Window* window, QueueFamilyIndices& queueFamilyIndices);

	/* Generic */
	void CreateSwapChain();
	void RecreateSwapChain();
	void CreateFrameBuffers(const VkImageView& depth_buffer, const std::vector<BufferImage>& color_buffer);
	void CleanUpSwapChain();
	void DestroyFrameBuffers();
	void DestroySwapChainImageViews();
	void DestroySwapChain();

	/* Getters */
	VkSwapchainKHR* GetSwapChainData();
	VkSwapchainKHR& GetSwapChain();
	uint32_t GetExtentWidth() const;
	uint32_t GetExtentHeight() const;
	VkExtent2D& GetExtent();
	VkFormat& GetSwapChainImageFormat();
	SwapChainDetails GetSwapChainDetails(VkPhysicalDevice& physicalDevice, VkSurfaceKHR& surface);

	/* Setters */
	void SetRenderPass(VkRenderPass* renderPass);
	void SetRecreationStatus(bool const status);

	/* Vectors operations */
	std::vector<VkFramebuffer>& GetFrameBuffers();
	size_t SwapChainImagesSize() const;
	size_t FrameBuffersSize() const;
	SwapChainImage* GetImage(uint32_t index);
	VkImageView& GetSwapChainImageView(uint32_t index);
	VkFramebuffer& GetFrameBuffer(uint32_t index);
	void PushImage(SwapChainImage swapChainImge);
	void PushFrameBuffer(VkFramebuffer frameBuffer);
	void ResizeFrameBuffers();
	
private:
	/* References of the renderer */
	MainDevice			*m_MainDevice;
	VkSurfaceKHR		*m_VulkanSurface;
	Window				*m_Window;	
	VkRenderPass		*m_RenderPass;

	QueueFamilyIndices  m_QueueFamilyIndices;


	/* Kernel Of the SwapChainHandler*/
	private:
	VkSwapchainKHR m_Swapchain;
	std::vector<SwapChainImage> m_SwapChainImages;
	std::vector<VkFramebuffer>  m_SwapChainFrameBuffers;

	VkFormat	 m_SwapChainImageFormat;
	VkExtent2D	 m_SwapChainExtent;

	bool m_IsRecreating = false;

private:
	VkSurfaceFormatKHR  ChooseBestSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& formats);
	VkPresentModeKHR	ChooseBestPresentationMode(const std::vector<VkPresentModeKHR>& presentationModes);
	VkExtent2D			ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& surfaceCapabilities);
};