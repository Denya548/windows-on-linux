//g++ Noise.cpp main.cpp TextureManager.cpp -o main -lSDL2 -lSDL2_image
#include "Noise.hpp"

using namespace std;

SDL_Event event;

Button but;

void Noise::init(const char *title, int posX, int posY, int width, int height, bool fullscrean){
	if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
		window = SDL_CreateWindow(title, posX, posY, width, height, 0);
		window2 = SDL_CreateWindow(title, posX, posY, width, height, 0);
		renderer = SDL_CreateRenderer(window, -1, 0);
		renderer2 = SDL_CreateRenderer(window2, -1, 0);
		isRunning = true;
		frame = 0;
		
		SDL_HideWindow(window2);
	}
}

void Noise::update(){
	frame++;
}

void Noise::handleEvents()
{
    while(SDL_PollEvent(&event)){
        switch (event.type)
        {
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym){
					case SDLK_q:
						isRunning = false;
						break;
					case SDLK_w:
						SDL_HideWindow(window2);
						break;
					case SDLK_s:
						SDL_ShowWindow(window2);
						break;
					default:
        				break;
				}
				break;

			case SDL_QUIT:
            	isRunning = false;
            	break;
        }
    };
}

void Noise::render(){
	SDL_SetRenderDrawColor(renderer, 32, 32, 32, 0);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer2, 64, 64, 64, 0);
	SDL_RenderClear(renderer2);
	//-------------------------------
	but.render(renderer2);
	//-------------------------------
	SDL_RenderPresent(renderer);
	SDL_RenderPresent(renderer2);
}

void Noise::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyWindow(window2);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyRenderer(renderer2);
    SDL_Quit();
 }
//g++ Noise.cpp main.cpp TextureManager.cpp -o main -lSDL2 -lSDL2_image
