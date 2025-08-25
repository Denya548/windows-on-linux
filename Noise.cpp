//g++ Noise.cpp main.cpp TextureManager.cpp -o main -lSDL2 -lSDL2_image
#include "Noise.hpp"

using namespace std;

SDL_Texture* grassTex;
SDL_Texture* sandTex;
SDL_Texture* waterTex;
SDL_Texture* redTex;
SDL_Event event;

Camera camera;
int tileSize = 32;
const int mapWidth = 60;
const int mapHeight = 34;
int seed = 1;
int infuenceRange = 10;
int infuencePointsNum = 100; //NUM POINT PER ONE SECTOR
int sector[mapHeight][mapWidth]; // like chank
std::vector<Tile> infuenceTiles; //ALL INFUENCE POINTS of SECTO
int waterMax = 20; //height generation water
int sandMax = 25;

int length(int x1, int y1, int x2, int y2){
	return(sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

void Noise::init(const char *title, int posX, int posY, int width, int height, bool fullscrean){
	if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
		window = SDL_CreateWindow(title, posX, posY, width, height, 0);
		renderer = SDL_CreateRenderer(window, -1, 0);
		isRunning = true;
		frame = 0;
		
		//INIT	
		grassTex = TextureManager::LoadTexture("Textures/Grass.png", renderer);
		sandTex = TextureManager::LoadTexture("Textures/Sand.png", renderer);
		waterTex = TextureManager::LoadTexture("Textures/Water.png", renderer);
		redTex = TextureManager::LoadTexture("Textures/Red.png", renderer);
	
		if(seed != 0){
			seed = time(nullptr);
			//seed = -100;
			srand(seed);
		}	
		//SDL_RenderSetScale(renderer,2 , 2);
	}
}



void Noise::update(){
	frame++;

	//CAMERA MOVEMENT
	camera.posX += camera.direct[0];	
	camera.posY += camera.direct[1];	

	infuenceTiles.clear();
		
		for(int y = 0; y < mapHeight; y++){
			for(int x = 0; x < mapWidth; x++){
					sector[y][x] = 0;
				}				
			}
		// RANDOM POITS
		int r;
		for(int y = -1 * infuenceRange + camera.posY; y < mapHeight + infuenceRange + camera.posY; y++){
			for(int x = -1 * infuenceRange + camera.posX; x < mapWidth + infuenceRange + camera.posX; x++){
				srand(seed + stoi(to_string(x) + to_string(y)));
				r = rand() % ((mapWidth + infuenceRange * 2) * (mapHeight + infuenceRange * 2));
				if(r <= infuencePointsNum){
					Tile tile;
					tile.posX = x;
					tile.posY = y;
					infuenceTiles.push_back(tile);
				}	
			}	
		}

		//NOISE GENERATION
		for(int y = 0; y < mapHeight; y++){
			for(int x = 0; x < mapWidth; x++){
				for(int i = 0; i < infuenceTiles.size(); i++){
					if(length(x + camera.posX, y + camera.posY, infuenceTiles[i].posX, infuenceTiles[i].posY) < infuenceRange){	
						sector[y][x] += infuenceRange - length(x + camera.posX, y + camera.posY, infuenceTiles[i].posX, infuenceTiles[i].posY); 						
					}	
				}				
			}
		}
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
						camera.direct[1] = -1;
						break;
					case SDLK_s:
						camera.direct[1] = 1;
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

SDL_Rect destR = {0, 0, 32, 32};	
void Noise::render(){
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	//-------------------------------
	for(int y = 0; y < mapHeight; y++){
		for(int x = 0; x < mapWidth; x++){
			destR.x = x * tileSize;
			destR.y = y * tileSize;
			if(sector[y][x] < waterMax){
				SDL_RenderCopy(renderer, waterTex ,NULL, &destR);
			}
			if(sector[y][x] >= waterMax && sector[y][x] <= sandMax){
				SDL_RenderCopy(renderer, sandTex ,NULL, &destR);
			}
			if(sector[y][x] > sandMax){
				SDL_RenderCopy(renderer, grassTex ,NULL, &destR);
			}			
		}
	}

	for(int i = 0; i < infuenceTiles.size(); i++){
		destR.x = (infuenceTiles[i].posX - camera.posX) * tileSize;
		destR.y = (infuenceTiles[i].posY - camera.posY) * tileSize;
		SDL_RenderCopy(renderer, redTex ,NULL, &destR);
	}

	//-------------------------------
	SDL_RenderPresent(renderer);
}

void Noise::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
 }

	//g++ Noise.cpp main.cpp TextureManager.cpp -o main -lSDL2 -lSDL2_image
				//srand(seed + stoi(to_string(x) + to_string(y)))
