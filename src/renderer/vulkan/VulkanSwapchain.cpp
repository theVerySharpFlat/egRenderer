//
// Created by aiden on 12/30/21.
//

#include <vulkan/vulkan.h>
#include <iostream>
#include <algorithm>
#include "VulkanSwapchain.h"
#include "VulkanDevice.h"

VulkanSwapchain::VulkanSwapchain(VulkanDevice* device, VkSurfaceKHR surface, Window *window) :
    m_device(device),
    m_surface(surface),
    m_window(window),
    m_physicalDevice(device->getPhysicalDevice()),
    m_logicalDevice(device->getLogicalDevice()),
    m_swapchain(VK_NULL_HANDLE)
    {
        SwapchainSettings settings = chooseSwapchainSettings();
        create(settings);
        createImageViews();
}

VulkanSwapchain::~VulkanSwapchain() {
    for(u32 i = 0; i < m_swapchainImageViewCount; i++) {
        vkDestroyImageView(m_logicalDevice, m_swapchainImageViews[i], nullptr);
    }
    vkDestroySwapchainKHR(m_device -> getLogicalDevice(), m_swapchain, nullptr);
    free(m_swapchainImages);
}

void VulkanSwapchain::create(SwapchainSettings settings) {
    m_swapchainSettings = settings;

    //we want more than the minimum image count, but less than the max image count
    u32 imageCount = settings.capabilities.minImageCount + 1;
    if(settings.capabilities.maxImageCount > 0 && imageCount > settings.capabilities.maxImageCount) {
        imageCount = settings.capabilities.maxImageCount;
    }

    VulkanDevice::QueueFamilyIndices indices = m_device -> getQueueFamilyIndices();
    u32 queueFamilyIndices[] = {
            indices.graphicsFamily.value(),
            indices.presentFamily.value()
    };

    VkSwapchainCreateInfoKHR createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface          = m_surface;
    createInfo.minImageCount    = imageCount;
    createInfo.imageFormat      = settings.surfaceFormat.format;
    createInfo.imageColorSpace  = settings.surfaceFormat.colorSpace;
    createInfo.imageExtent      = settings.extent;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage       = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    if(indices.presentFamily.value() != indices.presentFamily.value()) {
        std::cout << "present queue and graphics queue are different!" << std::endl;
        createInfo.imageSharingMode      = VK_SHARING_MODE_CONCURRENT;
        createInfo.queueFamilyIndexCount = 2;
        createInfo.pQueueFamilyIndices   = queueFamilyIndices;
    } else {
        createInfo.imageSharingMode      = VK_SHARING_MODE_EXCLUSIVE;
        createInfo.queueFamilyIndexCount = 0;
        createInfo.pQueueFamilyIndices   = nullptr;
    }
    createInfo.preTransform   = settings.capabilities.currentTransform;
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    createInfo.presentMode    = settings.presentMode;
    createInfo.clipped        = VK_TRUE;
    createInfo.oldSwapchain   = VK_NULL_HANDLE;

    if(vkCreateSwapchainKHR(m_device->getLogicalDevice(), &createInfo, nullptr,
                            &m_swapchain) != VK_SUCCESS) {
        std::cout << "failed to create swapchain!" << std::endl;
        exit(-1);
    }

    vkGetSwapchainImagesKHR(m_logicalDevice, m_swapchain, &m_swapchainImageCount,
                            nullptr);
    m_swapchainImages = (VkImage*) malloc(sizeof(VkImage) * m_swapchainImageCount);
    vkGetSwapchainImagesKHR(m_logicalDevice, m_swapchain, &m_swapchainImageCount,
                            m_swapchainImages);
}

VulkanSwapchain::SwapchainSettings VulkanSwapchain::chooseSwapchainSettings() {
    SwapchainSettings settings = {};

    //get surface capabilities for swap extent
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(m_physicalDevice, m_surface, &settings.capabilities);
    settings.extent = chooseSwapExtent(&settings.capabilities);

    //get present mode
    u32 presentModeCount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(m_physicalDevice, m_surface,
                                              &presentModeCount, nullptr);
    VkPresentModeKHR* presentModes = (VkPresentModeKHR*) alloca(sizeof(VkPresentModeKHR) * presentModeCount);
    vkGetPhysicalDeviceSurfacePresentModesKHR(m_physicalDevice, m_surface,
                                              &presentModeCount, presentModes);
    settings.presentMode = chooseSwapchainPresentMode(presentModes, presentModeCount);

    if(presentModeCount == 0) {
        std::cout << "physical device has no present modes! swapchain support inadequate!" << std::endl;
        exit(-1);
    }

    //get swap format
    u32 surfaceFormatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(m_physicalDevice, m_surface,
                                         &surfaceFormatCount, nullptr);
    VkSurfaceFormatKHR* surfaceFormats = (VkSurfaceFormatKHR*) alloca(sizeof(VkSurfaceFormatKHR) * surfaceFormatCount);
    vkGetPhysicalDeviceSurfaceFormatsKHR(m_physicalDevice, m_surface,
                                         &surfaceFormatCount, surfaceFormats);
    settings.surfaceFormat = chooseSwapSurfaceFormat(surfaceFormats, surfaceFormatCount);
    if(surfaceFormatCount == 0) {
        std::cout << "physical device has no surface formats! swapchain support inadequate!" << std::endl;
        exit(-1);
    }

    return settings;
}


VkSurfaceFormatKHR VulkanSwapchain::chooseSwapSurfaceFormat(const VkSurfaceFormatKHR *formats, u32 count) {
    for(u32 i = 0; i < count; i++) {
        if(formats[i].format == preferredSurfaceFormat && formats[i].colorSpace == preferredColorspace) {
            return formats[i];
        }
    }
    std::cout << "failed to find preferred surface format. Defaulting to formats[0]" << std::endl;
    return formats[0];
}

VkPresentModeKHR VulkanSwapchain::chooseSwapchainPresentMode(const VkPresentModeKHR *presentModes, u32 count) {
    for(u32 i = 0; i < count; i++) {
        if(presentModes[i] == preferredPresentMode) {
            return preferredPresentMode;
        }
    }
    return defaultPresentMode;
}

VkExtent2D VulkanSwapchain::chooseSwapExtent(const VkSurfaceCapabilitiesKHR *capabilities) {
    if(capabilities->currentExtent.width != UINT32_MAX) {
        return capabilities->currentExtent;
    } else {
        int width, height;
        m_window -> getFramebufferSize(&width, &height);

        VkExtent2D actualExtent = {
                static_cast<u32>(width),
                static_cast<u32>(height)
        };

        std::clamp(actualExtent.width, capabilities->minImageExtent.width, capabilities->maxImageExtent.width);
        std::clamp(actualExtent.height, capabilities->minImageExtent.height, capabilities->maxImageExtent.height);

        return actualExtent;
    }
}

void VulkanSwapchain::createImageViews() {
    m_swapchainImageViews = (VkImageView*) malloc(sizeof(VkImageView) * m_swapchainImageCount);

    for(u64 i = 0; i < m_swapchainImageCount; i++) {
        VkImageViewCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        createInfo.image = m_swapchainImages[i];
        createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        createInfo.format = m_swapchainSettings.surfaceFormat.format;

        createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

        createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        createInfo.subresourceRange.baseMipLevel = 0;
        createInfo.subresourceRange.levelCount = 1;
        createInfo.subresourceRange.baseArrayLayer = 0;
        createInfo.subresourceRange.layerCount = 1;

        if(vkCreateImageView(m_logicalDevice, &createInfo, nullptr, m_swapchainImageViews + i) != VK_SUCCESS) {
            std::cout << "failed to create image views!" << std::endl;
            exit(-1);
        }
    }
}