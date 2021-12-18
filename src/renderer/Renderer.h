//
// Created by aiden on 12/12/21.
//

#ifndef EGRENDERER_RENDERER_H
#define EGRENDERER_RENDERER_H


#include "Window.h"

class Renderer {
public:
    virtual void init(Window *window) = 0;
    virtual void shutdown() = 0;
    void sayHello();
};


#endif //EGRENDERER_RENDERER_H
