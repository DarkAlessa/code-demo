#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
//#define NDEBUG
#include <cassert>

#define assertm(exp, msg) assert(((void)msg, exp))
#define WIN_W 	640
#define WIN_H	480

struct FrameRate {
    FrameRate() = default;
    FrameRate(int fps) : FPS(fps) {}
    virtual ~FrameRate() = default;

    void start() {
        frameStart = SDL_GetTicks();
	    assertm(check == true, "function end() is not called.");
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

SDL_Color setColor(float time) {
	constexpr Uint8 rgb_max = 255;
	constexpr Uint8 rgb_min = 40;
	constexpr Uint8 limit   = (rgb_max - rgb_min) / 2;
	constexpr Uint8 up 		= limit + rgb_min;
	Uint8 r = static_cast<Uint8>(up + limit * std::sin((time/limit) + 0));
	Uint8 g = static_cast<Uint8>(up + limit * std::sin((time/limit) + 2));
	Uint8 b = static_cast<Uint8>(up + limit * std::sin((time/limit) + 4));
	return {r, g, b, 255};
}

struct Verlet {
	SDL_FRect dest;
	SDL_Color color  = {255, 255, 255, 255};
	SDL_FPoint pos   = {dest.x, dest.y};
	SDL_FPoint vel   = {3.0f, 4.0f};
	float mass       = 1.0f;
	SDL_FPoint force = {0.0f, 0.1f};
	SDL_FPoint acc   = {force.x / mass, force.y / mass};

	Verlet(SDL_FPoint&& p, SDL_Color&& color)
	: dest{p.x, p.y, 32.0f, 32.0f}
	, color{color}
	{}

    void update(float dt) {
        pos.x = pos.x + vel.x*dt + acc.x*dt*dt*0.5;
        pos.y = pos.y + vel.y*dt + acc.y*dt*dt*0.5;

        vel.x = vel.x + acc.x*dt*0.5;
        vel.y = vel.y + acc.y*dt*0.5;

        dest.x = pos.x;
        dest.y = pos.y;
    }

    void constrain() {
    	if (dest.x > WIN_W - dest.w) {
    		dest.x = WIN_W - dest.w;
    		vel.x *= -1.0f;
    		this->color = setColor(static_cast<float>(SDL_GetTicks64()/10));
    	}

    	if (dest.x < 0.0f) {
    		dest.x =  0.0f;
    		vel.x *= -1.0f;
    		this->color = setColor(static_cast<float>(SDL_GetTicks64()/10));
    	}

    	if (dest.y > WIN_H - dest.h) {
    		dest.y = WIN_H - dest.h;
    		vel.y *= -1.0f;
    		this->color = setColor(static_cast<float>(SDL_GetTicks64()/10));
    	}

    	if (dest.y < 0.0f) {
    		dest.y =  0.0f;
    		vel.y *= -1.0f;
    		this->color = setColor(static_cast<float>(SDL_GetTicks64()/10));
    	}
    }
};

int main(int argc, char** argv) {
//// Init
	assert((SDL_Init(SDL_INIT_EVERYTHING) == 0) && "SDL2 initialization failed.!");
	assert((TTF_Init() == 0) && "TTF initialization failed.!");
	constexpr int flags = IMG_InitFlags::IMG_INIT_JPG | IMG_InitFlags::IMG_INIT_PNG;
	if ((IMG_Init(flags) & flags) != flags) {
		std::cout << "IMG_Init() failed!!" << IMG_GetError() << '\n';
	}
	SDL_Window* window = SDL_CreateWindow("Verlet", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_W, WIN_H, SDL_WINDOW_SHOWN);
	assert(window && "error: can't create a window.!");
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	assert(renderer && "error: can't create a SDL_Renderer.!");
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

//// Verlet -----------------------------------
	SDL_Surface* imgSurface = IMG_Load("./assets/sprite/circle.png");
	assert(imgSurface && "IMG_Load() failed!");
	SDL_Texture* circle = SDL_CreateTextureFromSurface(renderer, imgSurface);
	assert(circle && "can't create texture from a surface.!");
	SDL_FreeSurface(imgSurface);

	std::vector<Verlet> verlet;

//// FPS --------------------------------------
    FrameRate fps(60);

//// Loop -------------------------------------
	bool running = true;
	while (running) {
        fps.start();
    //// Event    
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
	        switch (e.type) {
	            case SDL_EventType::SDL_QUIT:
	                running = false;
	                break;
				case SDL_EventType::SDL_KEYDOWN:
					switch (e.key.keysym.sym) {
						case SDL_KeyCode::SDLK_ESCAPE:
							running = false;
							break;
						default:
							break;
					}
				case SDL_EventType::SDL_MOUSEBUTTONDOWN:
					verlet.emplace_back(
									Verlet{SDL_FPoint{(float)(e.button.x - (32/2)), (float)(e.button.y - (32/2))},
										   SDL_Color{255, 255, 255, 255}});
					break;
	            default:
	            	break;
	       }
    	}

    	const Uint8* keys = SDL_GetKeyboardState(NULL);
        if (keys[SDL_GetScancodeFromKey(SDLK_c)]) verlet.clear();
        
    //// Render --------------------------------
		SDL_SetRenderDrawColor(renderer, 47, 52, 52, 255);
    	SDL_RenderClear(renderer);

    	if (!verlet.empty()) {
	    	for (auto& v : verlet) {
	    		v.update(1.0f);
	    		v.constrain();
	    		SDL_SetTextureColorMod(circle, v.color.r, v.color.g, v.color.b);
	    		SDL_RenderCopyExF(renderer, circle, NULL, &v.dest, 0, NULL, SDL_FLIP_NONE);
	    	}
    	}

    	SDL_RenderPresent(renderer);
        fps.end();
	}

//// Close ------------------------------------
    SDL_DestroyTexture(circle);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

	IMG_Quit();
    SDL_Quit();
	return 0;
}
