#include <iostream>
#include<SDL.h>
#undef main

#define SCREEN_WIDTH 384
#define SCREEN_HEIGHT 216

int main()
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window *window = SDL_CreateWindow(
		"Engine",
		SDL_WINDOWPOS_CENTERED_DISPLAY(0),
		SDL_WINDOWPOS_CENTERED_DISPLAY(0),
		1280,
		720,
		SDL_WINDOW_ALLOW_HIGHDPI);

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

	SDL_Texture* texture = SDL_CreateTexture(
		renderer,
		SDL_PIXELFORMAT_ABGR8888,
		SDL_TEXTUREACCESS_STREAMING,
		SCREEN_WIDTH,
		SCREEN_HEIGHT);

	uint32_t pixels[SCREEN_WIDTH * SCREEN_HEIGHT];
	memset(pixels, 0, sizeof(pixels));

	
	for (size_t i = 0; i < 50; i++)
	{
		pixels[int (SCREEN_HEIGHT / 2) * SCREEN_WIDTH + i] = 0xFF0000FF;
	}

	SDL_UpdateTexture(texture, NULL, pixels, SCREEN_WIDTH * 4);
	SDL_RenderCopyEx(
		renderer,
		texture,
		NULL,
		NULL,
		0.0,
		NULL,
		SDL_FLIP_VERTICAL);
	SDL_RenderPresent(renderer);

	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	return 0;
}