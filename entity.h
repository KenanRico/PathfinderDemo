#ifndef ENTITY_H
#define ENTITY_H
//------------------------------------
class Entity{
	public:
		SDL_Texture* texture;
		SDL_Rect srcrect;
		SDL_Rect dstrect;
		double angle;
		SDL_Point center;
		SDL_RendererFlip flip;
	public:
		Entity();
		~Entity();
};
//------------------------------------
#endif
