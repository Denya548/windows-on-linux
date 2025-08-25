#pragma once
#include "Noise.hpp"

struct TextureManager{
	static SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer* ren);
};
