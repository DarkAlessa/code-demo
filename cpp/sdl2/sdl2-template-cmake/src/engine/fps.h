#ifndef _FPS_H
#define _FPS_H
#include <SDL2/SDL_timer.h>

struct FrameRate {
    FrameRate();
    FrameRate(int);
    virtual ~FrameRate();
    void start();
    void end();
    void setFPS(unsigned int);

private:
    unsigned int FPS = 30;
    unsigned int frameDelay = 1000 / FPS;
    Uint64 frameStart;
    Uint64 frameTime;
    bool check = true;
};

#endif
