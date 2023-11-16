#include <iostream>
#include "SDL.h"

#include "Setup.h"

#define SCREEN_WIDTH 384
#define SCREEN_HEIGHT 216
namespace ChosEngine
{
	State::State(SDL_Window* _window, SDL_Texture* _texture, SDL_Renderer* _renderer, uint32_t* _pixels, bool _exit)
	{
		window = _window;
		texture = _texture;
		renderer = _renderer;
		pixels = _pixels;
		exit = _exit;
	}

	State* create()
	{
		SDL_Init(SDL_INIT_VIDEO);

		SDL_Window* window = SDL_CreateWindow(
			"Engine",
			SDL_WINDOWPOS_CENTERED_DISPLAY(0),
			SDL_WINDOWPOS_CENTERED_DISPLAY(0),
			1280,
			720,
			SDL_WINDOW_ALLOW_HIGHDPI);

		SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

		SDL_Texture* texture = SDL_CreateTexture(
			renderer,
			SDL_PIXELFORMAT_ABGR8888,
			SDL_TEXTUREACCESS_STREAMING,
			SCREEN_WIDTH,
			SCREEN_HEIGHT);

		uint32_t* pixels = new uint32_t[SCREEN_WIDTH * SCREEN_HEIGHT];
		memset(pixels, 0, sizeof(pixels));

		return new State(window, texture, renderer, pixels, false);
	}

	int destroy(State state)
	{
		SDL_DestroyTexture(state.texture);
		SDL_DestroyRenderer(state.renderer);
		SDL_DestroyWindow(state.window);

		delete[] state.pixels;
		return 0;
	}
}
