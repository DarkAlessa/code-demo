#include "game.h"
//#define NDEBUG
#include <cassert>

Game::Game(const char* title, int width, int height) : win_width(width), win_height(height) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << '\n';
        SDL_Quit();
        return;
    }

    // Create window
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, win_width, win_height, SDL_WINDOW_SHOWN);
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

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
}

Game::~Game() noexcept {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
};

void Game::setFPS(unsigned int fps) {
    this->fps.setFPS(fps);
}

void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        }
        
        if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window)) {
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

void Game::update() {
    // Update game logic here
    // Key state here
}

void Game::render() const {
    // Clear the screen
    SDL_SetRenderDrawColor(renderer, 204, 229, 255, 255);
    SDL_RenderClear(renderer);

    // Render game objects here

    // Update the screen
    SDL_RenderPresent(renderer);
}

void Game::run() {
    while (running) {
        fps.start();
        handleEvents();
        update();
        render();
        fps.end();
    }
}