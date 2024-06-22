#pragma once

#include <SDL2/SDL.h>
#include <string_view>

class Verlet {
public:
    Verlet(const char*, unsigned, unsigned);
    virtual ~Verlet();
    void run();

private:
    void handleEvents();
    void update();
    void render() const;

private:
    unsigned width;
    unsigned height;
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool running;
};
