#include "text.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
//#define NDEBUG
#include <cassert>

#define WIN_W	640
#define WIN_H	480
#define CENTER_X(cx) static_cast<float>(static_cast<int>((cx.x + (cx.w / 2.0f)) * 100)) / 100.0f
#define CENTER_Y(cy) static_cast<float>(static_cast<int>((cy.y + (cy.h / 2.0f)) * 100)) / 100.0f

double getAngle(const SDL_FRect& rectA, const SDL_FRect& rectB) {
	float delta_x = (rectB.x + (rectB.w / 2.0f)) - (rectA.x + (rectA.w / 2.0f));
	float delta_y = (rectA.y + (rectA.h / 2.0f)) - (rectB.y + (rectB.h / 2.0f));
	return std::atan2(delta_x, delta_y) * (180 / 3.14159);
}

void following(SDL_FRect& rectA, SDL_FRect& rectB, float speed) {
	float delta_x = (rectB.x + (rectB.w / 2.0f)) - (rectA.x + (rectA.w / 2.0f));
	float delta_y = (rectA.y + (rectA.h / 2.0f)) - (rectB.y + (rectB.h / 2.0f));
	float delta_d = delta_x / sin(std::atan2(delta_x, delta_y));
	if (delta_d > 50) {
		rectA.x += static_cast<float>(static_cast<int>((speed * cos(std::atan2(delta_y, delta_x))) * 100) / 100.0f);
		rectA.y -= static_cast<float>(static_cast<int>((speed * sin(std::atan2(delta_y, delta_x))) * 100) / 100.0f);
	}
	std::cout << delta_d << ", " << rectA.x << ", " << rectA.y << "\n";
}

int main(int argc, char** argv) {
    assert((SDL_Init(SDL_INIT_EVERYTHING) == 0) && "SDL2 initialization failed.!");
    assert((TTF_Init() == 0) && "TTF initialization failed.!");
	constexpr int flags = IMG_InitFlags::IMG_INIT_JPG | IMG_InitFlags::IMG_INIT_PNG;
	if ((IMG_Init(flags) & flags) != flags) {
		std::cout << "IMG_Init() failed!!" << IMG_GetError() << '\n';
	}
	SDL_Window* window = SDL_CreateWindow("Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_W, WIN_H, SDL_WINDOW_SHOWN);
    assert(window && "error: can't create a window.!");
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    assert(renderer && "error: can't create a SDL_Renderer.!");
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

/// Font -------------------------------------
	[[maybe_unused]] std::wstring icon = L"\uF0A4 \uF135 \uF427 \uF51C";

	[[maybe_unused]] Text textA("./assets/font/Audiowide-Regular.ttf", 10);
	textA.setColor(SDL_Color{109, 248, 147});
	textA.setPosition(SDL_FPoint{10.0f, 10.0f});

	[[maybe_unused]] Text textB = textA;
	textB.setPosition(SDL_FPoint{10.0f, 30.0f});

	std::stringstream st;
	
/// Image ------------------------------------
	SDL_Surface* imgSurface = IMG_Load("./assets/sprite/player_001.png");
	assert(imgSurface && "IMG_Load() failed!");
	SDL_FRect dest_1 = { 100.0f, 100.0f, static_cast<float>(imgSurface->w), static_cast<float>(imgSurface->h) };
	SDL_Texture* player_1 = SDL_CreateTextureFromSurface(renderer, imgSurface);
	assert(player_1 && "can't create texture from a surface.!");
	SDL_FreeSurface(imgSurface);
	imgSurface = nullptr;
		
	imgSurface = IMG_Load("./assets/sprite/player_002.png");
	assert(imgSurface && "IMG_Load() failed!");
	SDL_FRect dest_2 = { 400.0f, 400.0f, static_cast<float>(imgSurface->w), static_cast<float>(imgSurface->h) };
	SDL_Texture* player_2 = SDL_CreateTextureFromSurface(renderer, imgSurface);
	assert(player_2 && "can't create texture from a surface.!");	
	SDL_FreeSurface(imgSurface);
	imgSurface = nullptr;

/// FPS --------------------------------------
	constexpr int FPS = 60;
	constexpr int frameDelay = 1000 / FPS;
	Uint64 frameStart;
	Uint64 frameTime;

/// Loop -------------------------------------
	bool isRunning = true;
	while (isRunning) {
		frameStart = SDL_GetTicks64();
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
	        switch (e.type) {
	            case SDL_EventType::SDL_QUIT:
	                isRunning = false;
	                break;
				case SDL_EventType::SDL_MOUSEBUTTONDOWN:
					dest_1.x = e.button.x - (dest_1.w / 2);
					dest_1.y = e.button.y - (dest_2.h / 2);
					break;
	            default:
	            	break;
	        }
    	}

    /// Logic ----------------------------------------------------
        const Uint8* keys = SDL_GetKeyboardState(NULL);
        if (keys[SDL_GetScancodeFromKey(SDLK_a)]) dest_1.x -= 4.0f;
        if (keys[SDL_GetScancodeFromKey(SDLK_d)]) dest_1.x += 4.0f;
        if (keys[SDL_GetScancodeFromKey(SDLK_w)]) dest_1.y -= 4.0f;
        if (keys[SDL_GetScancodeFromKey(SDLK_s)]) dest_1.y += 4.0f;

    	if (dest_1.x >= (WIN_W - dest_1.w)) dest_1.x = (WIN_W - dest_1.w);
    	if (dest_1.x <= 0.0f)				dest_1.x = 0.0f;
    	if (dest_1.y >= (WIN_H - dest_1.h)) dest_1.y = (WIN_H - dest_1.h);
    	if (dest_1.y <= 0.0f)				dest_1.y = 0.0f;
    	
    	following(dest_2, dest_1, 0.6f);

    	st << CENTER_X(dest_1) << ", " << CENTER_Y(dest_1);
    	textB.setText(renderer, "Player: " + st.str());
    	st.str("");
      	st.clear();
    	st << CENTER_X(dest_2) << ", " << CENTER_Y(dest_2);
    	textA.setText(renderer, "Enemy: "  + st.str());
    	st.str("");
      	st.clear();

	/// Render ---------------------------------------------------
		SDL_SetRenderDrawColor(renderer, 47, 52, 52, 255);
    	SDL_RenderClear(renderer);
    	//---------------------------------------------------------
		SDL_SetRenderDrawColor(renderer, 160, 160, 160, 255);
		SDL_SetTextureColorMod(player_2, 243, 156, 254);
		SDL_RenderDrawLine(renderer, CENTER_X(dest_1), CENTER_Y(dest_1), CENTER_X(dest_2), CENTER_Y(dest_2));
		SDL_RenderDrawLine(renderer, CENTER_X(dest_1), 0.0f, CENTER_X(dest_1), static_cast<float>(WIN_H));
		SDL_RenderDrawLine(renderer, 0.0f, CENTER_Y(dest_1), static_cast<float>(WIN_W), CENTER_Y(dest_1));
		SDL_RenderDrawLine(renderer, CENTER_X(dest_1), CENTER_Y(dest_2), CENTER_X(dest_2), CENTER_Y(dest_2));
		SDL_RenderDrawLine(renderer, CENTER_X(dest_2), CENTER_Y(dest_1), CENTER_X(dest_2), CENTER_Y(dest_2));
		textB.render(renderer);
		textA.render(renderer);
		SDL_RenderCopyExF(renderer, player_1, NULL, &dest_1, getAngle(dest_1, dest_2), NULL, SDL_FLIP_NONE);
		SDL_RenderCopyExF(renderer, player_2, NULL, &dest_2, getAngle(dest_2, dest_1), NULL, SDL_FLIP_NONE);
		//---------------------------------------------------------
    	SDL_RenderPresent(renderer);

    /// End of FPS
    	frameTime = SDL_GetTicks64() - frameStart;
    	if (frameDelay > frameTime) {
    		SDL_Delay(frameDelay - frameTime);
    	}
	}

/// Close ------------------------------------
    textB.fontClose();
    textA.fontClose();
    SDL_DestroyTexture(player_1);
    SDL_DestroyTexture(player_2);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

	IMG_Quit();
    TTF_Quit();
    SDL_Quit();
	return 0;
}
