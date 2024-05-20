#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
//#define NDEBUG
#include <cassert>

#define WIN_W   640
#define WIN_H   480

struct FrameRate {
    FrameRate() = default;
    FrameRate(int fps) : FPS(fps) {}
    virtual ~FrameRate() = default;

    void start() {
        frameStart = SDL_GetTicks();
        assert(check == true && "function end() is not called.");
        check = false;
    }

    void end() {
        frameTime = SDL_GetTicks64() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
        check = true;
    }

private:
    unsigned int FPS = 30;
    unsigned int frameDelay = 1000 / FPS;
    Uint64 frameStart;
    Uint64 frameTime;
    bool check = true;
};

int main(int argc, char** argv) {
//// Init
    assert((SDL_Init(SDL_INIT_EVERYTHING) == 0) && "SDL2 initialization failed.!");
    assert((TTF_Init() == 0) && "TTF initialization failed.!");
    SDL_Window* window = SDL_CreateWindow("Verlet", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_W, WIN_H, SDL_WINDOW_SHOWN);
    assert(window && "error: can't create a window.!");
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    assert(renderer && "error: can't create a SDL_Renderer.!");
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

//// Font
    TTF_Font* font = TTF_OpenFont("./assets/font/Consola.TTF", 42);
    assert(font && "TTF_OpenFont failed.!");

    SDL_Color fg = {109, 248, 147, 255};
    SDL_Surface* text_surf = TTF_RenderText_Blended(font, "Hello World", fg);
    SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, text_surf);
    SDL_Rect dest;
    dest.x = (WIN_W / 2.0f) - (text_surf->w / 2.0f);
    dest.y = (WIN_H / 2.0f) - (text_surf->h / 2.0f);
    dest.w = text_surf->w;
    dest.h = text_surf->h;
    SDL_FreeSurface(text_surf);

//// FPS
    FrameRate fps(60);
    
//// Loop
    bool isRunning = true;
    while (isRunning) {
        fps.start();
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_EventType::SDL_QUIT:
                    isRunning = false;
                    break;
                default:
                    break;
            }
        }

    //// Rendering
        SDL_SetRenderDrawColor(renderer, 47, 52, 52, 255);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, text, NULL, &dest);

        SDL_RenderPresent(renderer);

    //// End of FPS
        fps.end();
    }

//// Close
    TTF_CloseFont(font);
    SDL_DestroyTexture(text);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();
    SDL_Quit();
    return 0;
}
