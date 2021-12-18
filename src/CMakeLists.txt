target_include_directories(egr PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_sources(egr PUBLIC renderer/Renderer.cpp Window.cpp)
add_subdirectory(renderer/vulkan)