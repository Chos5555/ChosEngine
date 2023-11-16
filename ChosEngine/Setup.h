#pragma once

namespace ChosEngine
{
	struct state {
		SDL_Window* window;
		SDL_Texture* texture;
		SDL_Renderer* renderer;

		bool exit;
	};

	state create();

	int destroy(state);
}
