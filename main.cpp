#include "Noise.hpp"
Noise noise;
int main(){
	const int fps = 60;
	const int frameDelay = 1000 / fps;
	Uint32 frameStart;
	int frameTime;
	noise.init("Noise", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, noise.width, noise.height, false);
	
	while(noise.isRunning){
		frameStart = SDL_GetTicks();

		noise.update();
		noise.handleEvents();
		noise.render();
		frameTime = SDL_GetTicks() - frameStart;
		if(frameDelay > frameTime){
			SDL_Delay(frameDelay - frameTime);
		}
	}
	noise.clean();
	return(0);
}
