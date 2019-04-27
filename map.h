#ifndef MAP_H
#define MAP_H
//-----------------------------------

#include "entity.h"

#include <vector>
#include <stdint.h>
#include <string>

class Map{
	private:
		std::vector<float>* mapping;
	public:
		uint16_t rows;
		uint16_t cols;
		Entity* path;
		Entity* wall;
		Entity* entrance;
		Entity* exit;
		uint16_t entrance_row; uint16_t entrance_col;
		uint16_t exit_row; uint16_t exit_col;
	public:
		Map();
		~Map();
	private:
		Map(const Map&) = delete;
		Map& operator=(const Map&) = delete;
	public:
		void ConfigMapping(int, int, const std::string&);
		void SetRenderEntities(Entity*, Entity*, Entity*, Entity*);
		const std::vector<float>& GetMapping() const;
};
//-----------------------------------
#endif
