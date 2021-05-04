struct MainDevice {
	VkPhysicalDevice PhysicalDevice;
	VkDevice		 LogicalDevice;
	VkDeviceSize	 MinUniformBufferOffset;
};

struct TextureObjects {
	std::vector<VkImage>		 TextureImages;
	std::vector<VkDeviceMemory>  TextureImageMemory;
	std::vector<VkImageView>	 TextureImageViews;
	std::vector<VkDescriptorSet> SamplerDescriptorSets;

	VkSampler					 TextureSampler = {};

	void CreateTextureSampler(MainDevice &mainDevice)
	{
		VkSamplerCreateInfo samplerCreateInfo = {};
		samplerCreateInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
		samplerCreateInfo.magFilter = VK_FILTER_LINEAR;		// linear interpolation between the texels
		samplerCreateInfo.minFilter = VK_FILTER_LINEAR;		// quando viene miniaturizzata come renderizzarla (lerp)
		samplerCreateInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
		samplerCreateInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
		samplerCreateInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
		samplerCreateInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
		samplerCreateInfo.unnormalizedCoordinates = VK_FALSE;			// � normalizzata
		samplerCreateInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
		samplerCreateInfo.mipLodBias = 0.0f;
		samplerCreateInfo.minLod = 0.0f;
		samplerCreateInfo.maxLod = 0.0f;
		samplerCreateInfo.anisotropyEnable = VK_TRUE;
		samplerCreateInfo.maxAnisotropy = 16;

		VkResult result = vkCreateSampler(mainDevice.LogicalDevice, &samplerCreateInfo, nullptr, &TextureSampler);
		if (result != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create a Texture Sampler!");
		}
	}

};

struct UboViewProjection {
	glm::mat4 projection;
	glm::mat4 view;
};

struct DepthBufferImage {
	VkImage			Image		= {};
	VkFormat		Format		= {};
	VkDeviceMemory  Memory		= {};
	VkImageView		ImageView	= {};

	void DestroyAndFree(MainDevice &mainDevice)
	{
		vkDestroyImageView(mainDevice.LogicalDevice, ImageView, nullptr);
		vkDestroyImage(mainDevice.LogicalDevice, Image, nullptr);
		vkFreeMemory(mainDevice.LogicalDevice, Memory, nullptr);
	}
};

struct SubmissionSyncObjects {
	VkSemaphore ImageAvailable; // Avvisa quanto l'immagine � disponibile
	VkSemaphore RenderFinished; // Avvisa quando il rendering � terminato
	VkFence		InFlight;			  // Fence per il frame in esecuzione
};

// Indici delle Queue Families presenti nel device fisico
struct QueueFamilyIndices {

	int GraphicsFamily	   = -1;
	int PresentationFamily = -1;

	bool isValid()
	{
		return GraphicsFamily >= 0 && PresentationFamily >= 0;
	}
};

struct Vertex
{
	glm::vec3 pos;
	glm::vec3 col;
	glm::vec2 tex;
};