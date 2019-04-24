#ifndef GAME_RESOURCES_H
#define GAME_RESOURCES_H
//------------------------------------

#include "map.h"
#include "character.h"
#include "entity.h"
#include "sdlresources.h"
#include "eventhandler.h"
#include "pathfinding/pathfinder.h"

#include <deque>
#include <stdint.h>
#include <vector>

#define GAME_GOOD 0
#define GAME_IMG_LOAD_FAIL 1
#define GAME_OVER 2

class GameResources{
	private:
		Map map;
		//Character chaser; uint64_t chaser_timer;
		std::vector<Character> chasers; uint64_t chaser_timer;
		Character runner; uint64_t runner_timer;
		std::deque<Entity> entities;
		Kha::PathFinder path_finder;
		uint8_t state;
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
};

//------------------------------------
#endif
