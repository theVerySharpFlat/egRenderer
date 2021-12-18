//
// Created by aiden on 12/17/21.
//

#ifndef EGRENDERER_VULKANRENDERER_H
#define EGRENDERER_VULKANRENDERER_H


#include "renderer/Renderer.h"
#include "Window.h"

class VulkanRenderer : public Renderer{
public:
    void init(Window *window) override;

    void shutdown() override;

private:
    Window* m_window;

    VkInstance m_instance;
    void createInstance();

    static const u32 requiredValidationLayerCount = 1;
    const char* validationLayers[requiredValidationLayerCount] = {
            "VK_LAYER_KHRONOS_validation"
    };
    bool checkValidationLayersSupport();

    const char** getRequiredExtensions(u32* count);
};


#endif //EGRENDERER_VULKANRENDERER_H
