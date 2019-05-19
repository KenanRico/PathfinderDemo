#include "gameresources.h"
#include "map.h"
#include "character.h"
#include "eventhandler.h"
//#include "pathfinding/pathfinder.h"
//#include "pathfinding/pos.h"
#include "pathfinding/include/pathfind.h"

#include <deque>
#include <iostream>
#include <cmath>
#include <cstring>
#include <fstream>
#include <sstream>

#include <SDL2/SDL.h>
#include <SDL2/extensions/SDL_image.h>


#define GAME_GOOD 0
#define GAME_IMG_LOAD_FAIL 1
#define GAME_LEVEL_LOAD_FAIL 2
#define	GAME_LEVEL_LOAD_FAIL_NOLEVEL 3
#define	GAME_LEVEL_LOAD_FAIL_UNRECOGNIZEDSETTING 4
#define	GAME_LEVEL_LOAD_FAIL_BADFORMAT 5
#define GAME_COMPLETE 6
#define GAME_OVER 7


GameResources::GameResources(const SDLResources& sdl): state(GAME_GOOD), next_level("maps/level_1.map"){
	//config state info
	state_info.resize(8);
	state_info[0] = "OK";
	state_info[1] = "Failed to load img";
	state_info[2] = "Failed to load level";
	state_info[3] = "Failed to load level (cannot find .map file)";
	state_info[4] = "Failed to load level (unrecognized setting in .map file)";
	state_info[5] = "Failed to load level (bad .map file formatting)";
	state_info[6] = "Complete";
	state_info[7] = "Over";
	//alloc entities
	entities.resize(5, Entity());
	SDL_Renderer* r = sdl.GetRenderer();
	//config map
	map.SetRenderEntities(&entities.at(0), &entities.at(1), &entities.at(2), &entities.at(3));
	SDL_Surface* surface = IMG_Load("textures/path.png");
	if(surface==nullptr){
		state = GAME_IMG_LOAD_FAIL;
		return;
	}
	map.path->texture = SDL_CreateTextureFromSurface(r, surface);
	SDL_QueryTexture(map.path->texture, nullptr, nullptr, &map.path->srect.w, &map.path->srect.h);
	SDL_FreeSurface(surface);
	surface = IMG_Load("textures/wall.png");
	if(surface==nullptr){
		state = GAME_IMG_LOAD_FAIL;
		return;
	}
	map.wall->texture = SDL_CreateTextureFromSurface(r, surface);
	SDL_FreeSurface(surface);
	SDL_QueryTexture(map.wall->texture, nullptr, nullptr, &map.wall->srect.w, &map.wall->srect.h);
	surface = IMG_Load("textures/entrance.png");
	if(surface==nullptr){
		state = GAME_IMG_LOAD_FAIL;
		return;
	}
	map.entrance->texture = SDL_CreateTextureFromSurface(r, surface);
	SDL_FreeSurface(surface);
	SDL_QueryTexture(map.entrance->texture, nullptr, nullptr, &map.entrance->srect.w, &map.entrance->srect.h);
	surface = IMG_Load("textures/exit.png");
	if(surface==nullptr){
		state = GAME_IMG_LOAD_FAIL;
		return;
	}
	map.exit->texture = SDL_CreateTextureFromSurface(r, surface);
	SDL_FreeSurface(surface);
	SDL_QueryTexture(map.exit->texture, nullptr, nullptr, &map.exit->srect.w, &map.exit->srect.h);
	//runner
	runner.SetRenderEntity(&entities.at(4));
	surface = IMG_Load("textures/runner.png");
	if(surface==nullptr){
		state = GAME_IMG_LOAD_FAIL;
		return;
	}
	runner.render_entity->texture = SDL_CreateTextureFromSurface(r, surface);
	SDL_QueryTexture(runner.render_entity->texture, nullptr, nullptr, &runner.render_entity->srect.w, &runner.render_entity->srect.h);
	SDL_FreeSurface(surface);

	LoadNextLevel(r);
}

GameResources::~GameResources(){


}


void GameResources::Update(const EventHandler& events, const SDLResources& sdl){
	//game end check
	for(int i=0; i<chasers.size(); ++i){
		if(chasers[i].row==runner.row && chasers[i].col==runner.col){
			state = GAME_OVER;
			return;
		}
	}
	int window_width = sdl.WindowW();
	int window_height = sdl.WindowH();
	int box_width = window_width/map.cols;
	int box_height = window_height/map.rows;
	//update map
	{
		Entity& entity = *map.path;
		entity.drect.w = box_width;
		entity.drect.h = box_height;
	}
	{
		Entity& entity = *map.wall;
		entity.drect.w = box_width;
		entity.drect.h = box_height;
	}
	{
		Entity& entity = *map.entrance;
		entity.drect.x = window_width * map.entrance_col / map.cols;
		entity.drect.y = window_height * map.entrance_row / map.rows;
		entity.drect.w = box_width;
		entity.drect.h = box_height;
	}
	{
		Entity& entity = *map.exit;
		entity.drect.x = window_width * map.exit_col / map.cols;
		entity.drect.y = window_height * map.exit_row / map.rows;
		entity.drect.w = box_width;
		entity.drect.h = box_height;
	}
	//update runner
	if(runner.timer++ % (10-runner.speed) == 0){
		const std::vector<float>& mapping = map.GetMapping();
		if(events[EventHandler::S] && runner.row<map.rows-1 && mapping[(runner.row+1)*map.cols+runner.col]==-1.0){
			runner.row += 1;
			runner.render_entity->angle = 180.0;
		}
		if(events[EventHandler::W] && runner.row>0 && mapping[(runner.row-1)*map.cols+runner.col]==-1.0){
			runner.row -= 1;
			runner.render_entity->angle = 0.0;
		}
		if(events[EventHandler::D] && runner.col<map.cols-1 && mapping[runner.row*map.cols+runner.col+1]==-1.0){
			runner.col += 1;
			runner.render_entity->angle = 90.0;
		}
		if(events[EventHandler::A] && runner.col>0 && mapping[runner.row*map.cols+runner.col-1]==-1.0){
			runner.col -= 1;
			runner.render_entity->angle = 270.0;
		}
		Entity& runner_entity = *runner.render_entity;
		runner_entity.drect.x = window_width*runner.col/map.cols;
		runner_entity.drect.y = window_height*runner.row/map.rows;
		runner_entity.drect.w = box_width;
		runner_entity.drect.h = box_height;
	}
	//update chaser
	for(int i=0; i<chasers.size(); ++i){
		Character& chaser = chasers[i];
		if(chaser.timer++%(10-chaser.speed)==0){
			if(sqrt(pow(runner.row-chaser.row,2)+pow(runner.col-chaser.col,2))<30.0f){
				const std::vector<float>& mapping = map.GetMapping();
				if(path_finder.FindPath(mapping, map.rows, map.cols, chaser.row, chaser.col, runner.row, runner.col)){
					const std::vector<Kha::Pos>& route = path_finder.GetRoute();
					chaser.row = route.at(0).row;
					chaser.col = route.at(0).col;
				}
			}
			Entity& chaser_entity = *chaser.render_entity;
			chaser_entity.drect.x = window_width*chaser.col/map.cols;
			chaser_entity.drect.y = window_height*chaser.row/map.rows;
			chaser_entity.drect.w = box_width;
			chaser_entity.drect.h = box_height;
		}
	}
	//level is complete if reach exit
	if(runner.row==map.exit_row && runner.col==map.exit_col){
		level_complete = true;
	}
}

void GameResources::Render(const SDLResources& sdl){
	SDL_Renderer* renderer = sdl.GetRenderer();
	int window_width = sdl.WindowW();
	int window_height = sdl.WindowH();
	SDL_RenderClear(renderer);
	//draw map
	const std::vector<float>& mapping = map.GetMapping();
	int size = mapping.size();
	for(int i=0; i<size; ++i){
		Entity& entity = entities[mapping[i]+2];
		entity.drect.x = window_width * (i%map.cols) / map.cols;
		entity.drect.y = window_height * (i/map.cols) / map.rows;
		SDL_RenderCopyEx(renderer, entity.texture, &entity.srect, &entity.drect, entity.angle, nullptr, entity.flip);
	}
	//draw characters
	size = entities.size();
	for(int i=2; i<size; ++i){
		Entity& entity = entities.at(i);
		if(!entity.enabled) continue;
		SDL_RenderCopyEx(renderer, entity.texture, &entity.srect, &entity.drect, entity.angle, nullptr, entity.flip);
	}
	SDL_RenderPresent(renderer);
	if(level_complete){
		LoadNextLevel(renderer);
		level_complete = false;
	}
}

uint8_t GameResources::State() const{
	return state;
}

const std::string& GameResources::StateStr() const{
	return state_info.at(state);
}


void GameResources::LoadNextLevel(SDL_Renderer* renderer){

	//deallocate current chasers and release render entities back into entity pool
	int size = entities.size();
	for(int i=5; i<size; ++i){
		entities.at(i).Disable();
	}
	chasers.clear();

	//if next level don't exist, game is complete
	if(next_level == ""){
		state = GAME_COMPLETE;
		return;
	};

	//stream file content into big string
	std::vector<std::string> file_content;
	std::ifstream ifs(next_level.c_str());
	if(ifs.fail()){
		state = GAME_LEVEL_LOAD_FAIL_NOLEVEL;
		return;
	}
	std::string line = "";
	while(getline(ifs, line)){
		file_content.push_back(line);
	}

	//next level waits to be set
	next_level = "";

	//parse file content and set up elements for new level
	int rows = 0; int cols = 0; std::string mapping_str = "";
	for(int i=0; i<file_content.size()-1; ++i){
		if(file_content.at(i).at(0)=='>'){
			const std::string& new_line = file_content.at(i++);
			if(new_line==">map_dimensions"){
				std::stringstream(file_content[i])>>rows>>cols;
			}else if(new_line==">map_mapping"){
				while(file_content.at(i).at(0)!='>'){
					mapping_str += file_content[i++];
				}
				--i;
			}else if(new_line==">map_entrance"){
				std::stringstream(file_content[i])>>map.entrance_row>>map.entrance_col;
				runner.row = map.entrance_row;
				runner.col = map.entrance_col;
				runner.speed = 7;
			}else if(new_line==">map_exit"){
				std::stringstream(file_content[i])>>map.exit_row>>map.exit_col;
			}else if(new_line==">chasers"){
				while(file_content.at(i).at(0)!='>'){
					int r = 0; int c = 0; int s=0;
					std::stringstream(file_content[i++])>>r>>c>>s;
					chasers.push_back(Character());
					Character& new_chaser = chasers.at(chasers.size()-1);
					new_chaser.row = r;
					new_chaser.col = c;
					new_chaser.speed = s;
					Entity* entity = nullptr;
					for(int i=5; i<entities.size(); ++i){
						if(!entities.at(i).enabled){
							entity = &entities.at(i);
							break;
						}
					}
					if(entity==nullptr){
						entities.push_back(Entity());
						entity = &entities.at(entities.size()-1);
						SDL_Surface* surface = IMG_Load("textures/chaser.png");
						if(surface==nullptr){
							state = GAME_IMG_LOAD_FAIL;
							return;
						}
						entity->texture = SDL_CreateTextureFromSurface(renderer, surface);
						SDL_QueryTexture(entity->texture, nullptr, nullptr, &entity->srect.w, &entity->srect.h);
						SDL_FreeSurface(surface);
					}
					new_chaser.SetRenderEntity(entity);
				}
				--i;
			}else if(new_line==">new_level"){
				next_level = std::string("maps/")+file_content.at(i);
			}else{
				state = GAME_LEVEL_LOAD_FAIL_UNRECOGNIZEDSETTING;
				break;
			}
		}else{
			std::cout<<file_content.at(i)<<"\n";
			state = GAME_LEVEL_LOAD_FAIL_BADFORMAT;
			break;
		}
	}
	map.ConfigMapping(rows, cols, mapping_str);
}
