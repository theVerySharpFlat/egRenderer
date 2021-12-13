//
// Created by aiden on 12/12/21.
//
#include <iostream>
#include <renderer/Renderer.h>

int main() {
    std::cout << "hello world" << std::endl;
    Renderer* renderer = new Renderer();
    renderer -> sayHello();
    delete renderer;
    return 0;
}