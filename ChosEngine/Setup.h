#pragma once

struct state {
	SDL_Window* window;
	SDL_Texture* texture;
	SDL_Renderer* renderer;


};

state create();

int destroy(state);