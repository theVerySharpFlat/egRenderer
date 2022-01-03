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
    QueueFamilyIndices getQueueFamilyIndices();

    VkPhysicalDevice& getPhysicalDevice() {
        return m_physicalDevice;

    }
    VkDevice& getLogicalDevice() {
        return m_device;
    }

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
    static const u32 physicalDeviceExtensionCount = 1;
    const char* physicalDeviceExtensions[physicalDeviceExtensionCount] = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };
    bool physicalDeviceSupportsExtensions(VkPhysicalDevice device);

    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
};


#endif //EGRENDERER_VULKANDEVICE_H
