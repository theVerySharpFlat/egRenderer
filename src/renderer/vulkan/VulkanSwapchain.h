//
// Created by aiden on 12/30/21.
//

#ifndef EGRENDERER_VULKANSWAPCHAIN_H
#define EGRENDERER_VULKANSWAPCHAIN_H


#include "types.h"
#include "Window.h"
#include "VulkanDevice.h"
#include <vector>

class VulkanSwapchain {
public:
    VulkanSwapchain(VulkanDevice* device, VkSurfaceKHR surface, Window *window);
    ~VulkanSwapchain();

private:
    VkSwapchainKHR   m_swapchain;
    u32              m_swapchainImageCount;
    VkImage*         m_swapchainImages;
    u32              m_swapchainImageViewCount;
    VkImageView*     m_swapchainImageViews;

    VulkanDevice*    m_device;
    VkDevice         m_logicalDevice;
    VkPhysicalDevice m_physicalDevice;
    VkSurfaceKHR     m_surface;
    Window*          m_window;

    struct SwapchainSettings {
        VkSurfaceCapabilitiesKHR  capabilities;
        VkSurfaceFormatKHR        surfaceFormat;
        VkPresentModeKHR          presentMode;
        VkExtent2D                extent;
    };
    SwapchainSettings m_swapchainSettings;
    SwapchainSettings chooseSwapchainSettings();

    static const VkFormat        preferredSurfaceFormat = VK_FORMAT_B8G8R8A8_SRGB;
    static const VkColorSpaceKHR preferredColorspace    = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const VkSurfaceFormatKHR* formats, u32 count);

    static const VkPresentModeKHR preferredPresentMode = VK_PRESENT_MODE_MAILBOX_KHR;
    static const VkPresentModeKHR defaultPresentMode   = VK_PRESENT_MODE_FIFO_KHR;
    VkPresentModeKHR chooseSwapchainPresentMode(const VkPresentModeKHR* presentModes, u32 count);

    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR* capabilities);

    void create(SwapchainSettings settings);

    void createImageViews();
};


#endif //EGRENDERER_VULKANSWAPCHAIN_H
