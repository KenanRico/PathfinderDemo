#ifndef GAME_RESOURCES_H
#define GAME_RESOURCES_H
//------------------------------------

#include "map.h"
#include "character.h"
#include "entity.h"
#include "sdlresources.h"
#include "eventhandler.h"
//#include "pathfinding/pathfinder.h"
#include "pathfinding/include/pathfind.h"

#include <deque>
#include <stdint.h>
#include <vector>
#include <string>

#include <SDL2/SDL.h>

class GameResources{
	private:
		Map map;
		//Character chaser; uint64_t chaser_timer;
		std::vector<Character> chasers;
		Character runner;
		std::deque<Entity> entities;
		Kha::PathFinder path_finder;
		bool level_complete;
		std::string next_level;
		uint8_t state;
		std::vector<std::string> state_info;
	public:
		GameResources(const SDLResources&);
		~GameResources();
	private:
		GameResources() = delete;
		GameResources(const GameResources&) = delete;
		GameResources& operator=(const GameResources&) = delete;

	public:
		void Update(const EventHandler&, const SDLResources&);
		void Render(const SDLResources&);
		uint8_t State() const;
		const std::string& StateStr() const;
	private:
		void LoadNextLevel(SDL_Renderer*);
};

//------------------------------------
#endif
