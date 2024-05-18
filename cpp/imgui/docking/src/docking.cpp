#include "my_win.h"
#include "../imgui/imgui.h"
#include "../imgui/backends/imgui_impl_sdl2.h"
#include "../imgui/backends/imgui_impl_sdlrenderer2.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include <cassert>

#define WIN_W         800
#define WIN_H         600
#define FPS           60
#define BORDER_RADIUS 4.0f

int main(int argc, char** argv) {
    // SDL init
    assert(SDL_Init(SDL_INIT_EVERYTHING) == 0);
    SDL_WindowFlags window_flags = static_cast<SDL_WindowFlags>(SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
    SDL_Window* window = SDL_CreateWindow("Demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_W, WIN_H, window_flags);
    assert(window);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    assert(renderer);
    SDL_SetWindowMinimumSize(window, WIN_W, WIN_H);

    // Window icon
    SDL_Surface* iconSurface = IMG_Load("./assets/icons/ig_like.png");
    assert(iconSurface);
    SDL_SetWindowIcon(window, iconSurface);
    SDL_FreeSurface(iconSurface);
    iconSurface = nullptr;

    // ImGui setting
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    //io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable DockSpace
    io.Fonts->AddFontFromFileTTF("./assets/fonts/Mitr-Regular.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesThai());

    ImGui::StyleColorsDark();
    ImGuiStyle& style = ImGui::GetStyle();
    style.TabRounding    = BORDER_RADIUS;
    style.FrameRounding  = BORDER_RADIUS;
    style.WindowRounding = BORDER_RADIUS;
    style.PopupRounding  = BORDER_RADIUS;
    style.WindowMinSize  = {240, 200};
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 1.0f);

    //// FPS --------------------------------------
    constexpr int frameDelay = 1000 / FPS;
    Uint64 start;
    Uint64 delta;

    // Loop
    bool running = true;
    while (running) {
        start = SDL_GetTicks64();
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                running = false;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
                running = true;
        }
        
        // Start the Dear ImGui frame
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        dockspace();
        my_window();

        // Rendering
        SDL_RenderSetScale(renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
        SDL_SetRenderDrawColor(renderer, (Uint8)(clear_color.x * 255), (Uint8)(clear_color.y * 255), (Uint8)(clear_color.z * 255), (Uint8)(clear_color.w * 255));
        SDL_RenderClear(renderer);

        SDL_Rect rect = {580, 380, 200, 200};
        SDL_SetRenderDrawColor(renderer, (Uint8)(rect_color.x * 255), (Uint8)(rect_color.y * 255), (Uint8)(rect_color.z * 255), (Uint8)(rect_color.w * 255));
        SDL_RenderFillRect(renderer, &rect);
        
        ImGui::Render();
        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
        SDL_RenderPresent(renderer);

        delta = SDL_GetTicks64() - start;
        if (frameDelay > delta) {
            SDL_Delay(frameDelay - delta);
        }
    }

    // Cleanup
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
