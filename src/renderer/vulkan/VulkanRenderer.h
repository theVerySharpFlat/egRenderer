//
// Created by aiden on 12/17/21.
//

#ifndef EGRENDERER_VULKANRENDERER_H
#define EGRENDERER_VULKANRENDERER_H


#include <vector>
#include "renderer/Renderer.h"
#include "Window.h"
#include "VulkanDevice.h"

class VulkanRenderer : public Renderer{
public:
    void init(Window *window) override;

    void shutdown() override;

private:
    Window* m_window;

    VkInstance m_instance;
    void createInstance();

    VulkanDevice* m_device;

    static const u32 requiredValidationLayerCount = 1;
    const char* validationLayers[requiredValidationLayerCount] = {
            "VK_LAYER_KHRONOS_validation"
    };
    VkDebugUtilsMessengerEXT debugMessenger;
    bool checkValidationLayersSupport();
    VkResult createDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
                                          const VkAllocationCallbacks *pAllocate,
                                          VkDebugUtilsMessengerEXT *pDebugMessenger);
    void destroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger,
                                       const VkAllocationCallbacks* pAllocate);
    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo);
    void setupDebugMessenger();

    std::vector<const char *> getRequiredExtensions(u32* count);
};


#endif //EGRENDERER_VULKANRENDERER_H
