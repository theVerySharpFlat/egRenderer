//
// Created by aiden on 12/12/21.
//
#include <iostream>
#include <renderer/Renderer.h>
#include "renderer/vulkan/VulkanRenderer.h"

int main() {
    std::cout << "hello world" << std::endl;
    Renderer* renderer = new VulkanRenderer();
    renderer -> sayHello();

    Window* window = new Window(800, 600);

    renderer -> init(window);
    while(!window -> shouldClose()) {
        window->pollEvents();
    }

    delete window;

    delete renderer;
    return 0;
}