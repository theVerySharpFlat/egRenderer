//
// Created by aiden on 12/17/21.
//

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

void Window::polllEvents() {
    glfwPollEvents();
}

void Window::shutdown() {
    glfwDestroyWindow(m_nativeWindow);
    glfwTerminate();
}

Window::~Window() {

}
