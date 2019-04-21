#include "map.h"
#include "entity.h"

#include <fstream>
#include <sstream>
#include <iostream>


Map::Map(const char* config_file): path(nullptr), wall(nullptr){
	std::ifstream fs(config_file);
	//fetch map dimensions from config
	std::string line = "";
	getline(fs, line);
	std::stringstream ss(line);
	ss>>rows>>cols;
	//fetch mapping from config
	std::string mapping_str = "";
	while(getline(fs, line)){
		mapping_str += line+" ";
	}
	mapping.resize(rows*cols);
	std::stringstream ss2(mapping_str);
	//for(uint16_t i=0; i<size; ++i){
	int i = 0;
	while(ss2>>mapping[i++]);
}

Map::~Map(){
	path->Disable();
	wall->Disable();
}

void Map::SetRenderEntities(Entity* p, Entity* w){
	path = p;
	wall = w;
	path->Enable();
	wall->Enable();
}

const std::vector<float>& Map::GetMapping() const{
	return mapping;
}
