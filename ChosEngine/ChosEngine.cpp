#include <iostream>
#include <SDL.h>

#include "ChosEngine.h"

#define SCREEN_WIDTH 384
#define SCREEN_HEIGHT 216
namespace ChosEngine
{
	template <typename T> T Sign(T a)
	{
		return (a < 0 ? -1 : (a > 0 ? 1 : 0));
	}

	template <typename T> T Min(T a, T b)
	{
		return a < b ? a : b;
	}

	template <typename T> T Max(T a, T b)
	{
		return a > b ? a : b;
	}

	void Engine::Rotate(float_t rotation)
	{
		const VectorFloat dir = state.direction, pla = state.viewPlane;
		state.direction.x = dir.x * cos(rotation) - dir.y * sin(rotation);
		state.direction.y = dir.x * sin(rotation) + dir.y * cos(rotation);
		state.viewPlane.x = pla.x * cos(rotation) - pla.y * sin(rotation);
		state.viewPlane.y = pla.x * sin(rotation) + pla.y * cos(rotation);
	}

	void Engine::Render()
	{
		for (size_t i = 0; i < 50; i++)
		{
			state.pixels[int(SCREEN_HEIGHT / 2) * SCREEN_WIDTH + i] = 0xFF0000FF;
		}
	}

	int Engine::Run()
	{
		map = *(new Map());
		state.position = map.startPosition;
		state.direction = map.startDirection;
		state.viewPlane = map.startViewPlane;

		while (!state.exit)
		{
			PollEvents();

			memset(state.pixels, 0, sizeof(state.pixels));

			Render();

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

	void Engine::PollEvents()
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				state.exit = true;
			else if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_UP:
					state.position.x += state.direction.x * state.moveSpeed;
					state.position.y += state.direction.y * state.moveSpeed;
					break;
				case SDLK_DOWN:
					state.position.x -= state.direction.x * state.moveSpeed;
					state.position.y -= state.direction.y * state.moveSpeed;
					break;
				case SDLK_LEFT:
					Rotate(+state.rotateSpeed);
					break;
				case SDLK_RIGHT:
					Rotate(-state.rotateSpeed);
					break;
				}
			}
		}
	}
}
