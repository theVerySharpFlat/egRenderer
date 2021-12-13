# egRenderer

This is the start of a renderer for the eugine engine.

### Why are you creating a renderer as a different project?

Because vulkan is going to make me type up a crap ton of code.
The way the engine is configured now, I can't integrate vulkan very easily without
going a long period of time without compiling and running, 
meaning I won't be able to test for all of the possible bugs my renderer will
give me.

Also, I need practice with vulkan.

### TODOS
1. Get a window up. This will most likely be very hacky as I don't want to 
write another eg::window
2. Create a vulkan instance and set up validation layers
3. Get physical/logical devices and queues
4. create swap chain
5. create pipeline
   1. shaders
   2. fixed function
   3. render passes
6. framebuffers
7. commandbuffers
8. presentation
9. vertex buffers
10. index buffers
11. uniform buffers
12. textures

### things to look into
1. vma (Vulkan Memory Allocator)
2. volk (vulkan loader)
3. command pool just for copy ops