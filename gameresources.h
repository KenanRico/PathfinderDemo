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
#include <string>

#include <SDL2/SDL.h>

#define GAME_GOOD 0
#define GAME_IMG_LOAD_FAIL 1
#define GAME_LEVEL_LOAD_FAIL 2
#define	GAME_LEVEL_LOAD_FAIL_NOLEVEL 3
#define	GAME_LEVEL_LOAD_FAIL_UNRECOGNIZEDSETTING 4
#define	GAME_LEVEL_LOAD_FAIL_BADFORMAT 5
#define GAME_COMPLETE 6
#define GAME_OVER 7

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
	private:
		void LoadNextLevel(SDL_Renderer*);
};

//------------------------------------
#endif
