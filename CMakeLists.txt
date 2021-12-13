project(egRenderer)

cmake_minimum_required(VERSION 3.17)

add_library(egr STATIC)

add_subdirectory(src)
add_subdirectory(test)