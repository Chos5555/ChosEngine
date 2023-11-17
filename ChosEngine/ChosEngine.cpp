#include <iostream>
#include <SDL.h>

#include "ChosEngine.h"
#include "Setup.h"

#define SCREEN_WIDTH 384
#define SCREEN_HEIGHT 216
namespace ChosEngine
{
	void Engine::Render(State state)
	{
		for (size_t i = 0; i < 50; i++)
		{
			state.pixels[int(SCREEN_HEIGHT / 2) * SCREEN_WIDTH + i] = 0xFF0000FF;
		}
	}

	int Engine::Run()
	{
		State state;
		
		while (!state.exit)
		{
			PollEvents(&state);

			memset(state.pixels, 0, sizeof(state.pixels));

			Render(state);

			SDL_UpdateTexture(state.texture, NULL, state.pixels, SCREEN_WIDTH * 4);
			SDL_RenderCopyEx(
				state.renderer,
				state.texture,
				NULL,
				NULL,
				0.0,
				NULL,
				SDL_FLIP_VERTICAL);
			SDL_RenderPresent(state.renderer);
		}

		state.destroy(state);
		return 0;
	}

	void Engine::PollEvents(State* state)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				state->exit = true;
			else if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_UP:
					break;
				case SDLK_DOWN:
					break;
				case SDLK_LEFT:
					break;
				case SDLK_RIGHT:
					break;
				}
			}
		}
	}
}
