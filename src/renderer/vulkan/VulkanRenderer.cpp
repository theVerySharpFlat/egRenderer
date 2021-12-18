//
// Created by aiden on 12/17/21.
//

#include <iostream>
#include "VulkanRenderer.h"
#include <cstring>

void VulkanRenderer::init(Window *window){
    m_window = window;
}

void VulkanRenderer::shutdown() {

}

const char **VulkanRenderer::getRequiredExtensions(u32* count) {
    return m_window -> getRequiredExtensions(count);
}

bool VulkanRenderer::checkValidationLayersSupport() {
    u32 layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    auto layerProperties = (VkLayerProperties*) alloca(sizeof(VkLayerProperties) * layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, layerProperties);

    for(auto & validationLayer : validationLayers) {
        bool layerFound = false;
        for(u32 j = 0; j < layerCount; j++) {
            if((bool)strcmp(validationLayer, layerProperties[j].layerName)) {
                layerFound = true;
                break;
            }
        }
        if(!layerFound)
            return false;
    }
    return true;
}


void VulkanRenderer::createInstance() {

    if(debugMessagingEnabled && !checkValidationLayersSupport()) {
        std::cout << "validation layers requested, but not available!" << std::endl;
        exit(-1);
    }

    //give vulkan some information about our engine
    VkApplicationInfo applicationInfo{};
    applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    applicationInfo.apiVersion = VK_API_VERSION_1_0;
    applicationInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    applicationInfo.pApplicationName = "eugine";
    applicationInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    applicationInfo.pEngineName = "Eugine Engine";

    //create the instance
    VkInstanceCreateInfo instanceCreateInfo{};
    instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceCreateInfo.pNext = nullptr;
    instanceCreateInfo.flags = 0;
    instanceCreateInfo.pApplicationInfo = &applicationInfo;

    if(debugMessagingEnabled) {
        instanceCreateInfo.enabledLayerCount = requiredValidationLayerCount;
        instanceCreateInfo.ppEnabledLayerNames = validationLayers;
    } else {
        instanceCreateInfo.enabledLayerCount = 0;
    }

    u32 extensionCount;
    const char** extensions = getRequiredExtensions(&extensionCount);
    instanceCreateInfo.enabledExtensionCount = extensionCount;
    instanceCreateInfo.ppEnabledExtensionNames = extensions;

    if(vkCreateInstance(&instanceCreateInfo, nullptr, &m_instance) != VK_SUCCESS) {
        std::cout << "failed to create vulkan instance" << std::endl;
        exit(-1);
    }
}