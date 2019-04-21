#include "gameresources.h"
#include "map.h"
#include "character.h"
#include "eventhandler.h"
#include "pathfinding/pathfinder.h"
#include "pathfinding/pos.h"

#include <deque>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/extensions/SDL_image.h>

#define PATHFINDING


GameResources::GameResources(const SDLResources& sdl): state(GAME_GOOD), map("maps/map1.conf"), chaser(21, 2), chaser_timer(0), runner(8, 42), runner_timer(0){
	entities.resize(4, Entity());
	SDL_Renderer* r = sdl.GetRenderer();
	//config map
	map.SetRenderEntities(&entities.at(0), &entities.at(1));
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
	//characters
	runner.SetRenderEntity(&entities.at(2));
	surface = IMG_Load("textures/runner.png");
	if(surface==nullptr){
		state = GAME_IMG_LOAD_FAIL;
		return;
	}
	runner.render_entity->texture = SDL_CreateTextureFromSurface(r, surface);
	SDL_QueryTexture(runner.render_entity->texture, nullptr, nullptr, &runner.render_entity->srect.w, &runner.render_entity->srect.h);
	SDL_FreeSurface(surface);

	chaser.SetRenderEntity(&entities.at(3));
	surface = IMG_Load("textures/chaser.png");
	if(surface==nullptr){
		state = GAME_IMG_LOAD_FAIL;
		return;
	}
	chaser.render_entity->texture = SDL_CreateTextureFromSurface(r, surface);
	SDL_QueryTexture(chaser.render_entity->texture, nullptr, nullptr, &chaser.render_entity->srect.w, &chaser.render_entity->srect.h);
	SDL_FreeSurface(surface);
}

GameResources::~GameResources(){


}


void GameResources::Update(const EventHandler& events, const SDLResources& sdl){
	//game end check
	if(chaser.row==runner.row && chaser.col==runner.col){
		state = GAME_OVER;
		return;
	}
	int window_width = sdl.WindowW();
	int window_height = sdl.WindowH();
	int box_width = window_width/map.cols;
	int box_height = window_height/map.rows;
	//update map
	Entity& map_path = *map.path;
	Entity& map_wall = *map.wall;
	map_path.drect.w = box_width;
	map_path.drect.h = box_height;
	map_wall.drect.w = box_width;
	map_wall.drect.h = box_height;
	//update runner
	if(runner_timer++ % 4 == 0){
		const std::vector<float>& mapping = map.GetMapping();
		if(events[EventHandler::S] && runner.row<map.rows && mapping[(runner.row+1)*map.cols+runner.col]==-1.0){
			runner.row += 1;
			runner.render_entity->angle = 180.0;
		}
		//runner.row -= (events[EventHandler::W] && runner.row>0 && mapping[(runner.row-1)*map.cols+runner.col]==-1.0)? 1 : 0;
		if(events[EventHandler::W] && runner.row>0 && mapping[(runner.row-1)*map.cols+runner.col]==-1.0){
			runner.row -= 1;
			runner.render_entity->angle = 0.0;
		}
		//runner.col += (events[EventHandler::D] && runner.col<map.cols && mapping[runner.row*map.cols+runner.col+1]==-1.0) ? 1 : 0;
		if(events[EventHandler::D] && runner.col<map.cols && mapping[runner.row*map.cols+runner.col+1]==-1.0){
			runner.col += 1;
			runner.render_entity->angle = 90.0;
		}
		//runner.col -= (events[EventHandler::A] && runner.col>0 && mapping[runner.row*map.cols+runner.col-1]==-1.0) ? 1 : 0;
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
	if(chaser_timer++ % 5 == 0){
		const std::vector<float>& mapping = map.GetMapping();
#ifdef PATHFINDING
		if(path_finder.FindPath(mapping, map.rows, map.cols, chaser.row, chaser.col, runner.row, runner.col)){
			const std::vector<Kha::Pos>& route = path_finder.GetRoute();
			chaser.row = route.at(0).row;
			chaser.col = route.at(0).col;
		}
#endif
		Entity& chaser_entity = *chaser.render_entity;
		chaser_entity.drect.x = window_width*chaser.col/map.cols;
		chaser_entity.drect.y = window_height*chaser.row/map.rows;
		chaser_entity.drect.w = box_width;
		chaser_entity.drect.h = box_height;
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
		SDL_RenderCopyEx(renderer, entity.texture, &entity.srect, &entity.drect, entity.angle, nullptr, entity.flip);
	}
	SDL_RenderPresent(renderer);
}

uint8_t GameResources::State() const{
	return state;
}
