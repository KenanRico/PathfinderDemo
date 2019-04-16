#include "sdlresources.h"
//#include "entity.h"

#include <iostream>

#include <SDL2/SDL.h>


SDLResources::SDLResources(): state(SDL_GOOD), window_width(800), window_height(600){
	//init sdl
	if(SDL_Init(SDL_INIT_EVERYTHING)!=0){
		state = SDL_INIT_FAILED;
		return;
	}
	//create window
	if((window=SDL_CreateWindow("Run", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_RESIZABLE)) == nullptr){
		state = SDL_WINDOW_CREATE_FAILED;
		return;
	}
	//create renderer
	if((renderer=SDL_CreateRenderer(window, -1, 0)) == nullptr){
		state = SDL_RENDERER_CREATE_FAILED;
		return;
	}
}

SDLResources::~SDLResources(){
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

uint8_t SDLResources::State() const{
	return state;
}

SDL_Renderer* GetRenderer() const{
	return renderer;
}

void SDLResources::Update(){
	SDL_GetWindowSize(window, &window_width, &window_height);
}

/*
void SDLResources::Render(const std::vector<Entity>& entities){
	SDL_RenderClear(renderer);
	uint8_t size = entities.size();
	for(uint8_t i=0; i<size; ++i){
		Entity& entity = entities.at();
		if(
			SDL_RenderCopyEx(
				renderer,
				entity.texture,
				entity.srcrect,
				entity.dstrect,
				entity.angle,
				entity.center,
				entity.hflip|entity.vflip
			) != 0
		){
			state = SDL_RENDER_FAILED;
			break;
		}
	}
	SDL_RenderPresent(renderer);
}
*/
