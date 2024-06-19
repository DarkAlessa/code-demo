#ifndef GAME_H
#define GAME_H

#include "engine/fps.h"
#include <iostream>
#include <string>
#include <SDL2/SDL.h>

class Game {
public:
    Game(const char*, int, int);
    virtual ~Game() noexcept;

    void setFPS(unsigned int);
    void run();

private:
    SDL_Window*   window   = nullptr;
    SDL_Renderer* renderer = nullptr;
    bool running   = false;
    FrameRate fps  = {60};
    int win_width;
    int win_height;

    void handleEvents();
    void update();
    void render() const;
};

#endif  // GAME_H