#ifndef GAME_RESOURCES_H
#define GAME_RESOURCES_H
//------------------------------------

#include "map.h"
#include "character.h"
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
			int8_t row;
			int8_t col;
		} Character;
	private:
		Map map;
		Character chaser;
		Character runner;
		std::vector<Entity> entities;
		PathFinder path_finder;
		uint8_t state;
	public:
		GameResources();
		~GameResources();
	private:
		GameResources(const GameResources&) = delete;
		GameResources& operator=(const GameResources&) = delete;
};

//------------------------------------
#endif
