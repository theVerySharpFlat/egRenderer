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
    VulkanDevice(VkInstance instance, const char **validationLayers, u32 validationLayerCount,
                 VkSurfaceKHR surface);
    ~VulkanDevice();

    struct QueueFamilyIndices {
        std::optional<u32> graphicsFamily;
        std::optional<u32> presentFamily;

        bool isComplete() {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

private:
    VkInstance m_instance;

    VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
    void pickPhysicalDevice();

    VkDevice m_device;
    void createLogicalDevice();

    const char** m_validationLayers;
    const u32 m_validationLayerCount;

    VkSurfaceKHR m_surface;

    bool isDeviceSuitable(VkPhysicalDevice device);

    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
};


#endif //EGRENDERER_VULKANDEVICE_H
