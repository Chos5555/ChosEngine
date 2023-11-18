#include <iostream>
#include <SDL.h>

#include "ChosEngine.h"

#define SCREEN_WIDTH 384
#define SCREEN_HEIGHT 216
namespace ChosEngine
{
	template <typename T> int8_t Sign(T a)
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

	void Engine::VerticalLine(int x, int y0, int y1, uint32_t color)
	{
		for (int y = y0; y < y1; y++)
		{
			state.pixels[(y * SCREEN_WIDTH) + x] = color;
		}
	}

	void Engine::Render()
	{
		for (int x = 0; x < SCREEN_WIDTH; x++)
		{
			const float_t xcam = (2 * (x / (float_t)(SCREEN_WIDTH))) - 1;

			const VectorFloat direction = {
				state.direction.x + state.viewPlane.x * xcam,
				state.direction.y + state.viewPlane.y * xcam,
			};

			VectorFloat position = state.position;
			VectorInt intPosition = { (int)position.x, (int)position.y, };

			const VectorFloat deltaDistance = {
				fabsf(direction.x) < 1e-20 ? (float_t)1e30 : (float_t)fabsf(1.0f / direction.x),
				fabsf(direction.y) < 1e-20 ? (float_t)1e30 : (float_t)fabsf(1.0f / direction.y),
			};

			VectorFloat sideDistance = {
				deltaDistance.x * (direction.x < 0 ?
					(position.x - intPosition.x) :
					(intPosition.x + 1 - position.x)),
				deltaDistance.y * (direction.y < 0 ?
					(position.y - intPosition.y) :
					(intPosition.y + 1 - position.y))
			};

			const VectorInt step = { (int)Sign(direction.x), (int)Sign(direction.y) };

			struct { int val, side; VectorFloat pos; } hit = { 0, 0, { 0.0f,0.0f } };

			while (!hit.val)
			{
				if (sideDistance.x < sideDistance.y)
				{
					sideDistance.x += deltaDistance.x;
					intPosition.x += step.x;
					hit.side = 0;
				}
				else
				{
					sideDistance.y += deltaDistance.y;
					intPosition.y += step.y;
					hit.side = 1;
				}

				hit.val = map.data[intPosition.y * map.size + intPosition.x];
			}

			uint32_t color;
			switch (hit.val) {
			case 1: color = 0xFF0000FF; break;
			case 2: color = 0xFF00FF00; break;
			case 3: color = 0xFFFF0000; break;
			case 4: color = 0xFFFF00FF; break;
			}

			if (hit.side == 1) {
				const uint32_t
					br = ((color & 0xFF00FF) * 0xC0) >> 8,
					g = ((color & 0x00FF00) * 0xC0) >> 8;

				color = 0xFF000000 | (br & 0xFF00FF) | (g & 0x00FF00);
			}

			hit.pos.x = position.x + sideDistance.x;
			hit.pos.y = position.y + sideDistance.y;

			const float_t dperp =
				hit.side == 0 ?
				(sideDistance.x - deltaDistance.x) :
				(sideDistance.y - deltaDistance.y);

			const int
				h = (int)(SCREEN_HEIGHT / dperp),
				y0 = Max((SCREEN_HEIGHT / 2) - (h / 2), 0),
				y1 = Min((SCREEN_HEIGHT / 2) + (h / 2), SCREEN_HEIGHT - 1);


			VerticalLine(x, 0, y0, 0xFF202020);
			VerticalLine(x, y0, y1, color);
			VerticalLine(x, y1, SCREEN_HEIGHT - 1, 0xFF505050);
		};
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
