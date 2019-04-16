#ifndef GAME_RESOURCES_H
#define GAME_RESOURCES_H
//------------------------------------

#include "entity.h"

#include <vector>

#define GAME_GOOD 0

class GameResources{
	public:
		typedef struct _Map{
			std::vector<float> mapping;
			int8_t rows;
			int8_t cols;
		} Map;
		typedef struct _Character{
			int8_t x;
			int8_t y;
		} Character;
		typedef struct _Entity{
			SDL_Texture* texture;
			SDL_Rect srcrect;
			SDL_Rect dstrect;
			double angle;
			SDL_Point center;
			SDL_RendererFlip flip;
		} Entity;
	private:
		Map map;
		Character chaser;
		Character runner;
		std::vector<Entity> entities;
		uint8_t state;
	public:
		GameResources();
		~GameResources();
	private:
		GameResources(const GameResources&) = delete;
		GameResources& operator=(const GameResources&) = delete;

	friend class Updater;
	friend class Renderer;
};

//------------------------------------
#endif
