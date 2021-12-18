project(egRenderer)

cmake_minimum_required(VERSION 3.17)

add_library(egr STATIC)

add_subdirectory(src)
add_subdirectory(test)

find_package(glfw3 REQUIRED)
find_package(Vulkan REQUIRED)

target_link_libraries(egr PRIVATE glfw Vulkan::Vulkan)