#ifndef GAME_H
#define GAME_H

#include "engine/fps.h"
#include <iostream>
#include <string>
#include <memory>
#include <SDL2/SDL.h>

class Game {
public:
    Game(const char*, int, int);
    ~Game();

    void setFPS(unsigned int);
    void run();

private:
    std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> window{nullptr, SDL_DestroyWindow};
    std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> renderer{nullptr, SDL_DestroyRenderer};
    bool running   = true;
    FrameRate fps  = {60};
    int win_width;
    int win_height;

    void handleEvents();
    void update();
    void render() const;
};

#endif  // GAME_H