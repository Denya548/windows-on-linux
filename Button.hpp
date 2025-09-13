#pragma once 
#include "Noise.hpp"

struct Button{
	SDL_Rect but[3] = {
		{0, 0, 100, 100},
		{0, 0, 100, 100 * 2},
		{0, 0, 100, 100 * 3},
	};
	void render(SDL_Renderer* rend){
		for(int i = 0; i < 3; i++){
			SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
			SDL_RenderDrawRect(rend, &but[i]);		
		}
	}	
};
