#include "app.h"
#include <SDL2/SDL_image.h>
//#define NDEBUG
#include <cassert>

App::App(const char* title, int width, int height) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << '\n';
        SDL_Quit();
        return;
    }

    // Create window
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window creation failed: " << SDL_GetError() << '\n';
        SDL_Quit();
        return;
    }

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        std::cerr << "Renderer creation failed: " << SDL_GetError() << '\n';
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }
}

App::~App() noexcept {
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
};

void App::set_fps(unsigned int fps) {
    this->fps.set_fps(fps);
}

void App::set_texture(const char* path) {
    SDL_Surface* surface = IMG_Load(path);
    assert(surface);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    assert(texture);
    SDL_FreeSurface(surface);
}

void App::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        }
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            des.x = event.button.x;
            des.y = event.button.y;
        }
    }
}

void App::update() {
    // Update game logic here
}

void App::render() {
    // Clear the screen
    SDL_SetRenderDrawColor(renderer, 60, 62, 62, 255);
    SDL_RenderClear(renderer);

    // Render game objects here
    SDL_RenderCopyEx(renderer, texture, NULL, &des, 0, NULL, SDL_FLIP_NONE);

    // Update the screen
    SDL_RenderPresent(renderer);
}

void App::run() {
    while (running) {
        fps.start();
        handleEvents();
        update();
        render();
        fps.end();
    }
}