#include "eventhandler.h"

#include <stdint.h>
#include <string>

#include <SDL2/SDL.h>

#define EVENTS_GOOD 0
#define EVENTS_END_GAME 1


EventHandler::EventHandler(): state(EVENTS_GOOD){
	keys.resize(4, false);
	state_info.resize(2);
	state_info[0] = "OK";
	state_info[1] = "Ended by user";
}

EventHandler::~EventHandler(){

}

void EventHandler::Update(){
	//reset
	//keys.at(A) = false;
	//keys.at(S) = false;
	//keys.at(D) = false;
	//keys.at(W) = false;
	//poll
	if(SDL_PollEvent(&events)){
		switch(events.type){
			case SDL_QUIT:
				state = EVENTS_END_GAME;
				break;
			case SDL_KEYDOWN:
				switch(events.key.keysym.sym){
					case SDLK_ESCAPE: state = EVENTS_END_GAME; break;
					case SDLK_a: keys.at(A) = true; break;
					case SDLK_s: keys.at(S) = true; break;
					case SDLK_d: keys.at(D) = true; break;
					case SDLK_w: keys.at(W) = true; break;
					default: /*other keys to be implemented in the future*/ break;
				}
				break;
			case SDL_KEYUP:
					switch(events.key.keysym.sym){
					case SDLK_a: keys.at(A) = false; break;
					case SDLK_s: keys.at(S) = false; break;
					case SDLK_d: keys.at(D) = false; break;
					case SDLK_w: keys.at(W) = false; break;
					default: /*every KEYUP correspond to a KEYDOWN*/ break;
				}
				break;
			default:
				break;
		}
	}
}

bool EventHandler::operator[](uint8_t i) const{
	return keys[i];
}

uint8_t EventHandler::State() const{
	return state;
}

const std::string& EventHandler::StateStr() const{
	return state_info.at(state);
}
