#ifndef ENTITY_H
#define ENTITY_H
//------------------------------------

#include <SDL2/SDL.h>

class Entity{
	public:
		SDL_Texture* texture;
		SDL_Rect srect;
		SDL_Rect drect;
		double angle;
		SDL_Point center;
		SDL_RendererFlip flip;
		bool enabled;
	public:
		Entity();
		~Entity();
	public:
		void Enable();
		void Disable();
};
//------------------------------------
#endif
