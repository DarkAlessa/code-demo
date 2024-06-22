#include "verlet.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl2.h"
#include "imgui/imgui_impl_sdlrenderer2.h"
#include <iostream>

Verlet::Verlet(const char* title, unsigned width, unsigned height)
:   width(width), height(height) {
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        std::cerr << "Warning: Linear texture filtering not enabled!" << '\n';
    }

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL Initialization failed" << SDL_GetError() << '\n';
        return;
    }

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window creation failed: " << SDL_GetError() << '\n';
        SDL_Quit();
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        std::cerr << "Renderer creation failed: " << SDL_GetError() << '\n';
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    running = true;
}

Verlet::~Verlet() {
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window)   SDL_DestroyWindow(window);
    SDL_Quit();
}

void Verlet::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
            break;
        }

        if (event.type == SDL_WINDOWEVENT &&
            event.window.event == SDL_WINDOWEVENT_CLOSE &&
            event.window.windowID == SDL_GetWindowID(window))
        {
            running = false;
            break;
        }

        if (event.type == SDL_EventType::SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDL_KeyCode::SDLK_ESCAPE) {
                running = false;
                break;
            }
        }
    }
}

void Verlet::update() {}

void Verlet::render() const {
    SDL_SetRenderDrawColor(renderer, 204, 229, 255, 255);
    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);
}

void Verlet::run() {
    while (running) {
        handleEvents();
        update();
        render();
    }
}
