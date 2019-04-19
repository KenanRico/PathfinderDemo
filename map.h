#ifndef MAP_H
#define MAP_H
//-----------------------------------

#include "entity.h"

#include <vector>
#include <stdint.h>

class Map{
	private:
		std::vector<float> mapping;
		uint16_t rows;
		uint16_t cols;
		Entity* path;
		Entity* wall;
	public:
		Map(const char*);
		~Map();
	private:
		Map() = delete;
		Map(const Map&) = delete;
		Map& operator=(const Map&) = delete;
	public:
		void SetRenderEntities(Entity*, Entity*);
};
//-----------------------------------
#endif
