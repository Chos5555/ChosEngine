#include <iostream>
#include <string>
#include <SDL.h>

#include "Setup.h"

#ifndef NDEBUG
#   define M_ASSERT(Expr, Msg) \
    _M_Assert(#Expr, Expr, __FILE__, __LINE__, Msg)
#else
#   define M_ASSERT(Expr, Msg) ;
#endif

#define SCREEN_WIDTH 384
#define SCREEN_HEIGHT 216
namespace ChosEngine
{
	void _M_Assert(const char* expr_str, bool expr, const char* file, int line, std::string msg)
	{
		if (!expr)
		{
			std::cerr << "Assert failed:\t" << msg << "\n"
				<< "Expected:\t" << expr_str << "\n"
				<< "Source:\t\t" << file << ", line " << line << "\n";
			abort();
		}
	}

	State::State(SDL_Window* _window, SDL_Texture* _texture, SDL_Renderer* _renderer, uint32_t* _pixels, bool _exit)
	{
		window = _window;
		texture = _texture;
		renderer = _renderer;
		pixels = _pixels;
		exit = _exit;
	}

	State::State()
	{
		M_ASSERT(
			!SDL_Init(SDL_INIT_VIDEO),
			std::string("SDL failed to initialize: %s\n") + SDL_GetError());

		window = SDL_CreateWindow(
			"Engine",
			SDL_WINDOWPOS_CENTERED_DISPLAY(0),
			SDL_WINDOWPOS_CENTERED_DISPLAY(0),
			1280,
			720,
			SDL_WINDOW_ALLOW_HIGHDPI);
		M_ASSERT(
			window,
			std::string("Failed to create SDL window: %s\n") + SDL_GetError());

			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
			M_ASSERT(
				renderer,
				std::string("Failed to create SDL renderer: %s\n") + SDL_GetError());

			texture = SDL_CreateTexture(
				renderer,
				SDL_PIXELFORMAT_ABGR8888,
				SDL_TEXTUREACCESS_STREAMING,
				SCREEN_WIDTH,
				SCREEN_HEIGHT);
		M_ASSERT(
			renderer,
			std::string("Failed to create SDL texture: %s\n") + SDL_GetError());

		pixels = new uint32_t[SCREEN_WIDTH * SCREEN_HEIGHT];
		memset(pixels, 0, sizeof(pixels));

		exit = false;
	}
	
	int State::destroy(State state)
	{
		SDL_DestroyTexture(state.texture);
		SDL_DestroyRenderer(state.renderer);
		SDL_DestroyWindow(state.window);

		delete[] state.pixels;
		return 0;
	}
}
