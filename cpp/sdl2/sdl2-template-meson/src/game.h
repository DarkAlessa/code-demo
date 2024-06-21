#ifndef GAME_H
#define GAME_H

#include "engine/fps.h"
#include <SDL2/SDL.h>

class Game {
public:
    Game(const char*, int, int);
    virtual ~Game() noexcept;

    void setFPS(unsigned int);
    void run();

private:
    void handleEvents();
    void update();
    void render() const;

private:
    int win_width;
    int win_height;
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool running = false;
    FrameRate fps{60};
};

#endif  // GAME_H