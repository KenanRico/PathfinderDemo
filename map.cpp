#include "map.h"
#include "entity.h"

#include <fstream>
#include <sstream>
#include <iostream>


Map::Map(): mapping(nullptr), path(nullptr), wall(nullptr){
}

Map::~Map(){
	if(mapping!=nullptr) delete mapping;
	path->Disable();
	wall->Disable();
}

void Map::ConfigMapping(int r, int c, const std::string& mapping_str){
	if(mapping!=nullptr) delete mapping;
	mapping = new std::vector<float>;
	rows = r; cols = c;
	mapping->resize(rows*cols);
	std::stringstream ss2(mapping_str);
	int i = 0;
	while(ss2>>*mapping[i++]);
}

void Map::SetRenderEntities(Entity* p, Entity* w){
	path = p;
	wall = w;
	path->Enable();
	wall->Enable();
}

const std::vector<float>& Map::GetMapping() const{
	return *mapping;
}
