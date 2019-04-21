#include "entity.h"

#include <SDL2/SDL.h>

Entity::Entity():
texture(nullptr),
srect({0,0,0,0}),
drect({0,0,0,0}),
angle(0.0),
center({0,0}),
flip(SDL_FLIP_NONE),
enabled(false){


}

Entity::~Entity(){
	if(texture!=nullptr){
		SDL_DestroyTexture(texture);
	}
}

void Entity::Enable(){
	enabled = true;
}

void Entity::Disable(){
	enabled = false;
}
