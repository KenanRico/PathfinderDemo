#ifndef SDL_RESOURCES_H
#define SDL_RESOURCES_H
//---------------------------------------

#include <vector>
#include <string>

#include <SDL2/SDL.h>

#define SDLR_FPS 60


class SDLResources{
	private:
		SDL_Window* window;
		int window_width;
		int window_height;
		SDL_Renderer* renderer;
		uint64_t frame_timestamp;
		uint8_t state;
		std::vector<std::string> state_info;
	public:
		SDLResources();
		~SDLResources();
	private:
		SDLResources(const SDLResources&) = delete;
		SDLResources& operator=(const SDLResources&) = delete;
	public:
		uint8_t State() const;
		const std::string& StateStr() const;
		SDL_Renderer* GetRenderer() const;
		void Update();
		int WindowW() const;
		int WindowH() const;
};

//---------------------------------------
#endif
