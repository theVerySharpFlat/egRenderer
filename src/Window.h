//
// Created by aiden on 12/17/21.
//

#ifndef EGRENDERER_WINDOW_H
#define EGRENDERER_WINDOW_H
//#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include "types.h"

class Window {
public:
    Window(int width, int height);

    bool shouldClose();
    void shutdown();
    void pollEvents();

    const char ** getRequiredExtensions(u32* count);
    void createWindowSurface(VkInstance &instance, VkSurfaceKHR* surface);

    void getFramebufferSize(int* width, int* height);

    ~Window();
private:
    GLFWwindow* m_nativeWindow;
    int m_width;
    int m_height;
};


#endif //EGRENDERER_WINDOW_H
