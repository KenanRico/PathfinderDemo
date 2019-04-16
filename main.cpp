#include "sdlresources.h"

#include <iostream>

#include <SDL2/SDL.h>


#ifdef main
#undef main
#endif


int main(){
	SDLResources sdl;
	while(sdl.State()==SDL_GOOD);
	/*
	//Resource class
	GameResource game;
	EventHandler events;
	//Loop
	while(sdl.State()==SDL_GOOD && game.State()==GAME_GOOD){
		sdl.Update();
		events.Update();
		game.Update(sdl, events);
		game.Render(sdl);
	}
	std::cout<<"SDL state: "<<sdl.State()<<"\nGame state: "<<game.State()<<"\n";
	*/
    return 0;
}
