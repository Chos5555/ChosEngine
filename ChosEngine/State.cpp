#include <iostream>
#include <string>
#include <SDL.h>

#include "State.h"

#ifndef NDEBUG
#   define M_ASSERT(Expr, Msg) \
    _M_Assert(#Expr, Expr, __FILE__, __LINE__, Msg)
#else
#   define M_ASSERT(Expr, Msg) ;
#endif

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

	State::State(
		SDL_Window* _window,
		SDL_Texture* _texture,
		SDL_Renderer* _renderer,
		uint32_t* _pixels,
		bool _exit,
		int32_t _screenWidth,
		int32_t _screenHeight,
		VectorFloat _position,
		VectorFloat _direction,
		VectorFloat _viewPlane,
		float_t _rotateSpeed,
		float_t _moveSpeed)
	{
		window = _window;
		texture = _texture;
		renderer = _renderer;
		pixels = _pixels;
		exit = _exit;
		screenWidth = _screenWidth;
		screenHeight = _screenHeight;
		position = _position;
		direction = _direction;
		viewPlane = _viewPlane;
		rotateSpeed = _rotateSpeed;
		moveSpeed = _moveSpeed;
	}

	State::State(int32_t _screenWidth, int32_t _screenHeight, float_t _rotateSpeed, float_t _moveSpeed)
	{
		screenWidth = _screenWidth;
		screenHeight = _screenHeight;

		rotateSpeed = _rotateSpeed;
		moveSpeed = _moveSpeed;

		exit = false;

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
				screenWidth,
				screenHeight);
		M_ASSERT(
			renderer,
			std::string("Failed to create SDL texture: %s\n") + SDL_GetError());

		pixels = new uint32_t[screenWidth * screenHeight];
		memset(pixels, 0, sizeof(pixels));
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
