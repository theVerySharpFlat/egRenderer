//
// Created by aiden on 12/18/21.
//

#include <alloca.h>
#include <iostream>
#include "VulkanDevice.h"
#include "types.h"


VulkanDevice::VulkanDevice(VkInstance instance) : m_instance(instance){
    pickPhysicalDevice();
}

VulkanDevice::~VulkanDevice() {

}

static VulkanDevice::QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device) {
    VulkanDevice::QueueFamilyIndices indices{};

    u32 queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    VkQueueFamilyProperties* queueFamilyProperties =
            (VkQueueFamilyProperties*) alloca(sizeof(VkQueueFamilyProperties) * queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    return indices;
}

static bool isDeviceSuitable(VkPhysicalDevice device) {
    VkPhysicalDeviceProperties deviceProperties;
    vkGetPhysicalDeviceProperties(device, &deviceProperties);

    VkPhysicalDeviceFeatures deviceFeatures;
    vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

    return true;
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


