#ifndef GAME_H
#define GAME_H

#include "engine/fps.h"
#include <memory>
#include <SDL2/SDL.h>

class Game {
public:
    Game(const char*, int, int);
    ~Game() noexcept;

    void setFPS(unsigned int);
    void run();

private:
    void handleEvents();
    void update();
    void render() const;

private:
    int win_width;
    int win_height;
    std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> window{nullptr, SDL_DestroyWindow};
    std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> renderer{nullptr, SDL_DestroyRenderer};
    bool running   = false;
    FrameRate fps{60};
};

#endif  // GAME_H