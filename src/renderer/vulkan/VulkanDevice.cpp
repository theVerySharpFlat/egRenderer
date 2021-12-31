//
// Created by aiden on 12/18/21.
//

#include <alloca.h>
#include <iostream>
#include "VulkanDevice.h"
#include "types.h"
#include "renderer/Renderer.h"

VulkanDevice::VulkanDevice(VkInstance instance, const char **validationLayers, u32 validationLayerCount,
                           VkSurfaceKHR surface)
    :m_instance(instance),
    m_validationLayerCount(validationLayerCount),
    m_validationLayers(validationLayers),
    m_surface(surface)
    {

    pickPhysicalDevice();
}

VulkanDevice::~VulkanDevice() {
    vkDestroyDevice(m_device, nullptr);
}

VulkanDevice::QueueFamilyIndices VulkanDevice::findQueueFamilies(VkPhysicalDevice device) {
    VulkanDevice::QueueFamilyIndices indices{};

    u32 queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    VkQueueFamilyProperties* queueFamilyProperties =
            (VkQueueFamilyProperties*) alloca(sizeof(VkQueueFamilyProperties) * queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilyProperties);

    for(int i = 0; i < queueFamilyCount; i++) {
        if(queueFamilyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            indices.graphicsFamily = i;
        }

        VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(device, i, m_surface, &presentSupport);

        if(presentSupport) {
            indices.presentFamily = i;
        }

        if(indices.isComplete()) {
            break;
        }
    }

    return indices;
}

bool VulkanDevice::isDeviceSuitable(VkPhysicalDevice device) {
    VkPhysicalDeviceProperties deviceProperties;
    vkGetPhysicalDeviceProperties(device, &deviceProperties);

    VkPhysicalDeviceFeatures deviceFeatures;
    vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

    //should implement selection based on whether it is an integrated gpu or discrete gpu
    VulkanDevice::QueueFamilyIndices indices = findQueueFamilies(device);

    //calculate if it is suitable
    bool suitable = indices.isComplete();

    return suitable;
}

void VulkanDevice::pickPhysicalDevice() {
    u32 deviceCount;
    vkEnumeratePhysicalDevices(m_instance, &deviceCount, nullptr);

    VkPhysicalDevice* devices = (VkPhysicalDevice*) alloca(sizeof(VkPhysicalDevice) * deviceCount);
    vkEnumeratePhysicalDevices(m_instance, &deviceCount, devices);

    for (int i = 0; i < deviceCount; ++i) {
        if(isDeviceSuitable(devices[i])) {
            m_physicalDevice = devices[i];
            break;
        }
    }

    if(m_physicalDevice == VK_NULL_HANDLE) {
        std::cout << "failed to find a suitable GPU!" << std::endl;
        exit(-1);
    }
}

void VulkanDevice::createLogicalDevice() {
    QueueFamilyIndices indices = findQueueFamilies(m_physicalDevice);

    VkDeviceQueueCreateInfo deviceQueueCreateInfo{};
    deviceQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    deviceQueueCreateInfo.queueCount = 1;
    deviceQueueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
    float queuePriority = 1.0f;
    deviceQueueCreateInfo.pQueuePriorities = &queuePriority;

    VkPhysicalDeviceFeatures deviceFeatures{};

    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.pQueueCreateInfos = &deviceQueueCreateInfo;
    createInfo.queueCreateInfoCount = 1;
    createInfo.pEnabledFeatures = &deviceFeatures;
    createInfo.enabledExtensionCount = 0;

    if(Renderer::debugMessagingEnabled) {
        createInfo.enabledLayerCount = m_validationLayerCount;
        createInfo.ppEnabledLayerNames = m_validationLayers;
    } else {
        createInfo.enabledLayerCount = 0;
    }

    if(vkCreateDevice(m_physicalDevice, &createInfo, nullptr, &m_device) != VK_SUCCESS) {
        std::cout << "failed to create logical device!" << std::endl;
        exit(-1);
    }

}
