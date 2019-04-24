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
	public:
		Map(int, int, const std::string&);
		~Map();
	private:
		Map() = delete;
		Map(const Map&) = delete;
		Map& operator=(const Map&) = delete;
	public:
		void ConfigMapping();
		void SetRenderEntities(Entity*, Entity*);
		const std::vector<float>& GetMapping() const;
};
//-----------------------------------
#endif
