#include "map.h"
#include "entity.h"

#include <sstream>
#include <iostream>


Map::Map(): mapping(nullptr), path(nullptr), wall(nullptr), entrance(nullptr), exit(nullptr){
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
	std::stringstream ss(mapping_str);
	int i = 0;
	while(ss>>(*mapping)[i++]);
}

void Map::SetRenderEntities(Entity* p, Entity* w, Entity* en, Entity* ex){
	path = p;
	wall = w;
	entrance = en;
	exit = ex;
	path->Enable();
	wall->Enable();
	entrance->Enable();
	exit->Enable();
}

const std::vector<float>& Map::GetMapping() const{
	return *mapping;
}
