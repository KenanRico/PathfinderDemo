#ifndef EVENT_HANDER_H
#define EVENT_HANDER_H

#include <stdint.h>
#include <vector>

#include <SDL2/SDL.h>

class EventHandler{
	public:
		enum Keys { S=0, W=1, D=2, A=3 };

	private:
		std::vector<bool> keys;
		SDL_Event events;
		uint8_t state;

	public:
		EventHandler();
		~EventHandler();
	private:
		EventHandler(const EventHandler&) = delete;
		EventHandler& operator=(const EventHandler&) = delete;
	public:
		void Update();
		bool KeyDown(uint8_t) const;
		bool operator[](uint8_t) const;
		uint8_t State() const;
};

#endif
