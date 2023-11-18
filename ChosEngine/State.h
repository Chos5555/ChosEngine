#pragma once

#include <SDL.h>

#include "Vector.h"

#define SCREEN_WIDTH 384
#define SCREEN_HEIGHT 216

namespace ChosEngine
{
	class State{
	public:
		SDL_Window* window;
		SDL_Texture* texture;
		SDL_Renderer* renderer;

		uint32_t* pixels;

		bool exit;

		int32_t screenWidth;
		int32_t screenHeight;

		VectorFloat position;
		VectorFloat direction;
		VectorFloat viewPlane;

		float_t rotateSpeed;
		float_t moveSpeed;

		State(int32_t _screenWidth, int32_t _screenHeight, float_t _rotateSpeed, float_t _moveSpeed);

		State(
			SDL_Window* _window,
			SDL_Texture* _texture,
			SDL_Renderer* _renderer,
			uint32_t* _pixels,
			bool _exit,
			int32_t screenWidth,
			int32_t screenHeight,
			VectorFloat position,
			VectorFloat direction,
			VectorFloat viewPlane,
			float_t rotateSpeed,
			float_t moveSpeed);

		int destroy(State state);
	};
}
