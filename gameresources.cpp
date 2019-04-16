#include "gameresources.h"
#include "map.h"
#include "character.h"
#include "eventhandler.h"






GameResources::GameResources(): state(GAME_GOOD), map("map1"), chaser(17, 95), runner(107, 36){
	entities.resize(4, Entity());
	//config map
	map.SetRenderEntityIndices(0,1);
	entities.at(map.EntityIndex(0)).texture = ...
	entities.at(map.EntityIndex(1)).texture = ...
	runner.SetRenderEntityIndex(2);
	entities.at(runner.EntityIndex()).texture = ...
	chaser.SetRenderEntityIndex(3);
	entities.at(chaser.EntityIndex()).texture = ...
}

GameResources::~GameResources(){


}


void GameResources::Update(){
	//update map

	//update runner
	runner.row += events.KeyDown(EventHandler::S) ? 0 : 1;
	runner.row -= events.KeyDown(EventHandler::W) ? 0 : 1;
	runner.col += events.KeyDown(EventHandler::D) ? 0 : 1;
	runner.col -= events.KeyDown(EventHandler::A) ? 0 : 1;
	uint8_t index = runner.EntityIndex();
	entities.at(index).dstrect.x = windows_width*runner.col/map.cols;
	entities.at(index).dstrect.y = windows_height*runner.row/map.rows;
	entities.at(index).angle = 0.0;
	//update chaser
	if(path_finder.FindPath(map.mapping, map.rows, map.cols, chaser.row, chaser.col, runner.row, runner.col)){
		const std::vector<...>& route = path_finder.GetRoute();
		chaser.row = route.at(0).row;
		chaser.col = route.at(0).col;
	}
	index = chaser.EntityIndex();
	entities.at(index).dstrect.x = windows_width*chaser.col/map.cols;
	entities.at(index).dstrect.y = windows_height*chaser.row/map.rows;

}
