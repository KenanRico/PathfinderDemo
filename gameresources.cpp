#include "gameresources.h"
#include "map.h"
#include "character.h"
#include "eventhandler.h"

#include <deque>





GameResources::GameResources(): state(GAME_GOOD), map("map1"), chaser(17, 95), runner(107, 36){
	entities.resize(4, Entity());
	//config map
	map.SetRenderEntities(&entities.at(0), &entities.at(1));
	map.path.texture = ...
	map.wall.texture = ...
	//characters
	runner.SetRenderEntity(&entities.at(2));
	runner.sprite.texture = ...
	chaser.SetRenderEntityIndex(&entities.at(3));
	chaser.sprite.texture = ...
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
	Entity& entity = *runner.sprite;
	entity.dstrect.x = windows_width*runner.col/map.cols;
	entity.dstrect.y = windows_height*runner.row/map.rows;
	entity.angle = 0.0;
	//update chaser
	if(path_finder.FindPath(map.mapping, map.rows, map.cols, chaser.row, chaser.col, runner.row, runner.col)){
		const std::vector<...>& route = path_finder.GetRoute();
		chaser.row = route.at(0).row;
		chaser.col = route.at(0).col;
	}
	entity = *chaser.sprite;
	entity.dstrect.x = windows_width*chaser.col/map.cols;
	entity.dstrect.y = windows_height*chaser.row/map.rows;

}
