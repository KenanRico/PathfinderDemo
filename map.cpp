#include "map.h"
#include "entity.h"




Map::Map(const char* config_file): path(nullptr), wall(nullptr){
	std::ofstream fs(config_file);
	//fetch map dimensions from config
	std::string line = "";
	getline(fs, line);
	std::stringstream ss(line);
	ss>>rows>>cols;
	//fetch mapping from config
	std::string mapping_str = "";
	while(getline(fs, line)){
		mapping_str += line+",";
	}
	mapping.reserve(rows*cols);
}

Map::~Map(){
	path.Disable();
	wall.Disable();
}

void Map::SetRenderEntities(Entity* p, Entity* w){
	path = p;
	wall = w;
}

