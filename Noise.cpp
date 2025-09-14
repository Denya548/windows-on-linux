//g++ Noise.cpp main.cpp TextureManager.cpp -o main -lSDL2 -lSDL2_image
#include "Noise.hpp"

using namespace std;

SDL_Event event;
SDL_Window* windows[2];

Button but;
int mousePos[2];

void Noise::init(const char *title, int posX, int posY, int width, int height, bool fullscrean){
	if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
		windows[0] = SDL_CreateWindow(title, posX, posY, width, height, 0);
		windows[1] = SDL_CreateWindow(title, posX, posY, width, height, 0);
		renderer[0] = SDL_CreateRenderer(windows[0], -1, 0);
		renderer[1] = SDL_CreateRenderer(windows[1], -1, 0);
		isRunning = true;
		frame = 0;
		
		SDL_HideWindow(windows[1]);
	}
}
Uint32 mouseState;
void Noise::update(){
	mouseState = SDL_GetMouseState(&mousePos[0], &mousePos[1]);
	
	//printf("%d\n", SDL_GL_GetCurrentWindow() == window2);
	frame++;
}

void Noise::handleEvents()
{
    while(SDL_PollEvent(&event)){
		if(event.type == SDL_MOUSEMOTION && event.motion.windowID == SDL_GetWindowID(windows[1])){
			but.window2IsCurrent = true;	
		}
		else{
			but.window2IsCurrent = false;	
		}
        switch (event.type)
        {
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym){
					case SDLK_q:
						isRunning = false;
						break;
					case SDLK_s:
						SDL_HideWindow(windows[1]);
						break;
					case SDLK_w:
						SDL_ShowWindow(windows[1]);
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
	SDL_SetRenderDrawColor(renderer[0], 32, 32, 32, 0);
	SDL_RenderClear(renderer[0]);

	SDL_SetRenderDrawColor(renderer[1], 64, 64, 64, 0);
	SDL_RenderClear(renderer[1]);
	//-------------------------------
	but.render(renderer[1], mousePos);
	//-------------------------------
	SDL_RenderPresent(renderer[0]);
	SDL_RenderPresent(renderer[1]);
}

void Noise::clean(){
    SDL_DestroyWindow(windows[0]);
    SDL_DestroyWindow(windows[1]);
    SDL_DestroyRenderer(renderer[0]);
    SDL_DestroyRenderer(renderer[1]);
    SDL_Quit();
 }
//g++ Noise.cpp main.cpp TextureManager.cpp -o main -lSDL2 -lSDL2_image
