#ifndef ENTITY_H
#define ENTITY_H
//------------------------------------
class Entity{
	private:
		SDL_Texture* texture;
		SDL_Rect srcrect;
		SDL_Rect dstrect;
		double angle;
		SDL_Point center;
		SDL_RendererFlip flip;
	public:
		Entity(const std::string&, int,int,int,int, int,int,int,int, bool);
		~Entity();

};
//------------------------------------
#endif

				entity.texture,
				entity.srcrect,
				entity.dstrect,
				entity.angle,
				entity.center,
				entity.hflip|entity.vflip
