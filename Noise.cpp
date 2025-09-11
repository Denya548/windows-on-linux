//g++ Noise.cpp main.cpp TextureManager.cpp -o main -lSDL2 -lSDL2_image
#include "Noise.hpp"

using namespace std;

SDL_Event event;

Camera camera;
int seed = 1;

int length(int x1, int y1, int x2, int y2){
	return(sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

void Noise::init(const char *title, int posX, int posY, int width, int height, bool fullscrean){
	if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
		window = SDL_CreateWindow(title, posX, posY, width, height, 0);
		window2 = SDL_CreateWindow(title, posX, posY, width, height, 0);
		renderer = SDL_CreateRenderer(window, -1, 0);
		renderer2 = SDL_CreateRenderer(window2, -1, 0);
		isRunning = true;
		frame = 0;
		
		if(seed == 0){
			seed = time(nullptr);
		}	
		srand(seed);
		//SDL_RenderSetScale(renderer,2 , 2);
	}
}

void Noise::update(){
	frame++;

	camera.posX += camera.direct[0] * camera.speed;	
	camera.posY += camera.direct[1] * camera.speed;	
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
						camera.direct[1] = -1;
						break;
					case SDLK_s:
						camera.direct[1] = 1;
						SDL_ShowWindow(window2);
						break;
					case SDLK_a:
						camera.direct[0] = -1;
						break;
					case SDLK_d:
						camera.direct[0] = 1;
						break;
					default:
        				break;
				}
				break;

			case SDL_KEYUP:
				switch (event.key.keysym.sym){
					case SDLK_w:
						camera.direct[1] = 0;
						break;
					case SDLK_s:
						camera.direct[1] = 0;
						break;
					case SDLK_a:
						camera.direct[0] = 0;
						break;
					case SDLK_d:
						camera.direct[0] = 0;
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
	SDL_SetRenderDrawColor(renderer, 0, 128, 0, 0);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer2, 128, 0, 0, 0);
	SDL_RenderClear(renderer2);
	//-------------------------------

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
