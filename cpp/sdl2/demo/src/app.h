#ifndef APP_H
#define APP_H

#include "fps.h"
#include <SDL2/SDL.h>

class App {
public:
    App(const char*, int, int);
    virtual ~App();

    void set_fps(unsigned int);
    void set_texture(const char*);
    void run();

private:
    void handleEvents();
    void update();
    void render();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    bool running = false;
    SDL_Rect des{120, 120, 60, 60};
    FrameRate fps{60};
};

#endif