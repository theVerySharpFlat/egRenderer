//
// Created by aiden on 12/17/21.
//

#include <iostream>
#include "VulkanRenderer.h"
#include <cstring>

void VulkanRenderer::init(Window *window){
    m_window = window;
    createInstance();
}

void VulkanRenderer::shutdown() {
    delete m_device;

    if(debugMessagingEnabled)
        destroyDebugUtilsMessengerEXT(m_instance, debugMessenger, nullptr);

    vkDestroyInstance(m_instance, nullptr);
}

std::vector<const char *> VulkanRenderer::getRequiredExtensions(u32* count) {
    u32 windowExtensionCount;
    const char** windowExtensions = m_window->getRequiredExtensions(&windowExtensionCount);

    std::vector<const char*> extensions(windowExtensions, windowExtensions + windowExtensionCount);

    if (debugMessagingEnabled) {
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    return extensions;
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

    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
    if(debugMessagingEnabled) {
        instanceCreateInfo.enabledLayerCount = requiredValidationLayerCount;
        instanceCreateInfo.ppEnabledLayerNames = validationLayers;

        populateDebugMessengerCreateInfo(debugCreateInfo);
        instanceCreateInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debugCreateInfo;
    } else {
        instanceCreateInfo.enabledLayerCount = 0;
    }

    u32 extensionCount;
    auto extensions = getRequiredExtensions(&extensionCount);
    instanceCreateInfo.enabledExtensionCount = extensionCount;
    instanceCreateInfo.ppEnabledExtensionNames = extensions.data();

    for(auto extension : extensions) {
        std::cout << '\t' << extension << std::endl;
    }

    if(vkCreateInstance(&instanceCreateInfo, nullptr, &m_instance) != VK_SUCCESS) {
        std::cout << "failed to create vulkan instance" << std::endl;
        exit(-1);
    }

    //create device
    m_device = new VulkanDevice(m_instance, validationLayers, requiredValidationLayerCount);
}