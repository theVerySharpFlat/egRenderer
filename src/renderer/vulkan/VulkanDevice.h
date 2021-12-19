//
// Created by aiden on 12/18/21.
//

#ifndef EGRENDERER_VULKANDEVICE_H
#define EGRENDERER_VULKANDEVICE_H
#include <vulkan/vulkan.h>
#include "types.h"
#include <optional>

class VulkanDevice {
public:
    VulkanDevice(VkInstance instance);
    ~VulkanDevice();

    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;
    };

private:
    VkInstance m_instance;

    VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
    void pickPhysicalDevice();
};


#endif //EGRENDERER_VULKANDEVICE_H
