#include "sdlresources.h"
//#include "entity.h"

#include <iostream>

#include <SDL2/SDL.h>


#define SDLR_GOOD 0
#define SDLR_INIT_FAILED 1
#define SDLR_WINDOW_CREATE_FAILED 2
#define SDLR_RENDERER_CREATE_FAILED 3
#define SDLR_RENDER_FAILED 4


SDLResources::SDLResources(): state(SDLR_GOOD), window_width(800), window_height(600), frame_timestamp(0){
	//config state info
	state_info.resize(5);
	state_info[0] = "Ok";
	state_info[1] = "Failed to init SDL";
	state_info[2] = "Failed to create window";
	state_info[3] = "Failed to create renderer";
	state_info[4] = "Failed to render";
	//init sdl
	if(SDL_Init(SDL_INIT_EVERYTHING)!=0){
		state = SDLR_INIT_FAILED;
		return;
	}
	//create window
	if((window=SDL_CreateWindow("Run", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_RESIZABLE)) == nullptr){
		state = SDLR_WINDOW_CREATE_FAILED;
		return;
	}
	//create renderer
	if((renderer=SDL_CreateRenderer(window, -1, 0)) == nullptr){
		state = SDLR_RENDERER_CREATE_FAILED;
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

const std::string& SDLResources::StateStr() const{
	return state_info.at(state);
}

SDL_Renderer* SDLResources::GetRenderer() const{
	return renderer;
}

void SDLResources::Update(){
	//dimension
	SDL_GetWindowSize(window, &window_width, &window_height);
	//frame limiting
	uint64_t delta_time = SDL_GetTicks() - frame_timestamp;
	frame_timestamp = SDL_GetTicks();
	int64_t delay_time = 1000/SDLR_FPS - delta_time;
	if(delay_time>0){
		SDL_Delay(delay_time);
	}
}

int SDLResources::WindowW() const{
	return window_width;
}

int SDLResources::WindowH() const{
	return window_height;
}
