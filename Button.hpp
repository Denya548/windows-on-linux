#pragma once 
#include "Noise.hpp"

struct Button{
	SDL_Rect but[3] = {
		{0, 100, 100, 100},
		{0, 100 * 2, 100, 100},
		{0, 100 * 3, 100, 100},
	};
	bool window2IsCurrent = false;
	void render(SDL_Renderer* rend, int m[2]){
		for(int i = 0; i < 3; i++){
			if(but[i].x < m[0] && m[0] < but[i].x + but[i].w &&
		  	   but[i].y < m[1] && m[1] < but[i].y + but[i].h && window2IsCurrent){	
				SDL_SetRenderDrawColor(rend, 100, 0, 0, 64);
			}
			else{	
				SDL_SetRenderDrawColor(rend, 32, 32, 32, 0);
			}

			SDL_RenderFillRect(rend, &but[i]);		
		}
	}	
};
