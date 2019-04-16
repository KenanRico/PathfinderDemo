#include "entity.h"

#include <SDL2/SDL.h>

Entity::Entity(): 
texture(nullptr),
srcrect({0,0,0,0}),
dstrect({0,0,0,0}),
angle(0.0),
center(0,0),
flip(NO_FLIP){


}

~Entity(){
	if(texture!=nullptr){
		SDL_FreeTexture(texture);
	}
}
