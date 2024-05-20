#include "fps.h"
//#define NDEBUG
#include <cassert>
#define assertm(exp, msg) assert(((void)msg, exp))

FrameRate::FrameRate() = default;

FrameRate::FrameRate(int fps) : FPS(fps) {}

FrameRate::~FrameRate() noexcept = default;

void FrameRate::start() {
    frameStart = SDL_GetTicks();
    assertm(check == true, "function end() is not called.");
    check = false;
}

void FrameRate::end() {
    frameTime = SDL_GetTicks64() - frameStart;
    if (frameDelay > frameTime) {
        SDL_Delay(frameDelay - frameTime);
    }
    check = true;
}

void FrameRate::set_fps(unsigned int fps) {
    FPS = fps;
}