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
	bool isRunning;
	SDL_Window *window;
	int width = 1920;
	int height = 1080;
	void init(const char* title, int posX, int posY, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();
	int frame = 0;
};
