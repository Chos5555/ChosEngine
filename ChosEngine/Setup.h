#pragma once

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

		State(
			SDL_Window* _window,
			SDL_Texture* _texture,
			SDL_Renderer* _renderer,
			uint32_t* _pixels,
			bool _exit);
	};

	State* create();

	int destroy(State state);
}
