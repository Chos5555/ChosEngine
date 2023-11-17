#pragma once

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

		// TODO: Move define macro values to here, set in constructor
		int32_t screenWidth;
		int32_t screenHeight;

		VectorFloat position;
		VectorFloat direction;
		VectorFloat viewPlane;

		float_t rotateSpeed;
		float_t moveSpeed;

		State();

		State(
			SDL_Window* _window,
			SDL_Texture* _texture,
			SDL_Renderer* _renderer,
			uint32_t* _pixels,
			bool _exit);

		int destroy(State state);
	};
}
