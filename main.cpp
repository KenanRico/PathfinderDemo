#include "sdlresources.h"
#include "eventhandler.h"
#include "gameresources.h"

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/extensions/SDL_image.h>


#ifdef main
#undef main
#endif


int main(){
	SDLResources sdl;
	EventHandler events;
	GameResources game(sdl);
	while((sdl.State()|events.State()|game.State())==0x00){
		sdl.Update();
		events.Update();
		game.Update(events, sdl);
		game.Render(sdl);
	}
	std::cout<<"SDL state: "<<(int)sdl.State()<<"\nEvent state: "<<(int)events.State()<<"\nGame stat: "<<(int)game.State()<<"\n";
    return 0;
}
