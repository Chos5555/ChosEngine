#include <iostream>
#include <SDL.h>

#include "ChosEngine.h"
#include "Setup.h"

#define SCREEN_WIDTH 384
#define SCREEN_HEIGHT 216
namespace ChosEngine
{
	int Engine::Run()
	{
		state state = create();

		uint32_t *pixels = new uint32_t[SCREEN_WIDTH * SCREEN_HEIGHT];
		
		while (!state.exit)
		{
			SDL_Event event;
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
					state.exit = true;
			}

			memset(pixels, 0, sizeof(pixels));


			for (size_t i = 0; i < 50; i++)
			{
				pixels[int(SCREEN_HEIGHT / 2) * SCREEN_WIDTH + i] = 0xFF0000FF;
			}

			SDL_UpdateTexture(state.texture, NULL, pixels, SCREEN_WIDTH * 4);
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

		delete[] pixels;
		destroy(state);
		return 0;
	}
}
