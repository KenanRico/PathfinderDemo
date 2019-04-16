#ifndef SDL_RESOURCES_H
#define SDL_RESOURCES_H
//---------------------------------------

//#include "entity.h"

#include <SDL2/SDL.h>

#define SDL_GOOD 0
#define SDL_INIT_FAILED 1
#define SDL_WINDOW_CREATE_FAILED 2
#define SDL_RENDERER_CREATE_FAILED 3
#define SDL_RENDER_FAILED 4

class SDLResources{
	private:
		SDL_Window* window;
		int window_width;
		int window_height;
		SDL_Renderer* renderer;
		uint8_t state;
	public:
		SDLResources();
		~SDLResources();
	private:
		SDLResources(const SDLResources&) = delete;
		SDLResources& operator=(const SDLResources&) = delete;
	public:
		uint8_t State() const;
		SDL_Renderer* GetRenderer() const;
		//void Render(const std::vector<Entity>&);

	friend class Updater;
};

//---------------------------------------
#endif
