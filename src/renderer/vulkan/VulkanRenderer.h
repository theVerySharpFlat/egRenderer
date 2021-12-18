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
};


#endif //EGRENDERER_VULKANRENDERER_H
