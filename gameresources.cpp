






GameResources::GameResources(): state(GAME_GOOD), map("map1"), chaser(17, 95), runner(107, 36){
	entities.resize(3, Entity());
	map.SetRenderEntityIndex(0);
	runner.SetRenderEntityIndex(1);
	chaser.SetRenderEntityIndex(2);
}

GameResources::~GameResources(){


}


void GameResources::Update(){
	//update map

	//update runner
	if(events[EventHandler::W]){
		--runner.y;
	}
	if(events[EventHandler::A]){
		--runner.x;
	}
	if(events[EventHandler::S]){
		++runner.y;
	}
	if(events[EventHandler::D]){
		++runner.x;
	}
	entities[1].Update(runner.x, runner.y);
	//update chaser
	if(path_finder.FindPath(map.mapping, map.rows, map.cols, chaser.y, chaser.x, runner.y, runner.x)){
		const std::vector<...>& route = path_finder.GetRoute();
		chaser.x = route.at(0).col;
		chaser.y = route.at(0).row;
	}
	entities[2].Update(chaser.x, chaser.y);

}
