#pragma once
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <vector>
#include "TextureManager.hpp"
#include <cstdlib>
#include <cmath>
#include <ctime>
#include "Tile.hpp"
#include <string>
#include "Camera.hpp"

struct Noise{
	SDL_Renderer *renderer;
	SDL_Renderer *renderer2;
	bool isRunning;
	SDL_Window *window;
	SDL_Window *window2;
	int width = 910;
	int height = 540;
	void init(const char* title, int posX, int posY, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();
	int frame = 0;
};
