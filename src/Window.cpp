//
// Created by aiden on 12/17/21.
//

#include <iostream>
#include "Window.h"

Window::Window(int width, int height) : m_height(height), m_width(width) {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    m_nativeWindow = glfwCreateWindow(width, height, "vulkan window", nullptr, nullptr);
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(m_nativeWindow);
}

void Window::pollEvents() {
    glfwPollEvents();
}

const char ** Window::getRequiredExtensions(u32 *count) {
    return glfwGetRequiredInstanceExtensions(count);
}

void Window::createWindowSurface(VkInstance &instance, VkSurfaceKHR *surface) {
    auto result = glfwCreateWindowSurface(instance, m_nativeWindow, nullptr, surface);
    if(result != VK_SUCCESS) {
        std::cout << "failed to create window surface" << std::endl;
        exit(-1);
    }
}

void Window::shutdown() {
    glfwDestroyWindow(m_nativeWindow);
    glfwTerminate();
}

Window::~Window() {

}
