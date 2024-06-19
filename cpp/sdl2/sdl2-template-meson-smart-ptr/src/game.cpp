#include "game.h"
//#define NDEBUG
#include <cassert>

Game::Game(const char* title, int width, int height) : win_width(width), win_height(height) {
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        std::cerr << "Warning: Linear texture filtering not enabled!" << std::endl;
    }
    
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << '\n';
        return; // No need to call SDL_Quit() because SDL was not initialized
    }

    // Create window
    window.reset(SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, win_width, win_height, SDL_WINDOW_SHOWN));
    if (!window) {
        std::cerr << "Window creation failed: " << SDL_GetError() << '\n';
        SDL_Quit(); // SDL was initialized, so we need to clean up
        return;
    }

    // Create renderer
    renderer.reset(SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
    if (!renderer) {
        std::cerr << "Renderer creation failed: " << SDL_GetError() << '\n';
        window.reset();  // Clean up window if renderer creation fails
        SDL_Quit();
        return;
    }

    running = true;
}

Game::~Game() noexcept {
    if (renderer.get()) renderer.reset();
    if (window.get()) window.reset();
    SDL_Quit();
}

void Game::setFPS(unsigned int fps) {
    this->fps.setFPS(fps);
}

void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        }
        
        if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window.get())) {
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
    SDL_SetRenderDrawColor(renderer.get(), 204, 229, 255, 255);
    SDL_RenderClear(renderer.get());

    // Render game objects here

    // Update the screen
    SDL_RenderPresent(renderer.get());
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