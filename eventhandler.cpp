

EventHandler::EventHandler(): state(EVENTS_GOOD){
	keys.resize(4, false);
}

EventHandler::~EventHandler(){

}

void EventHandler::Update(){
	SDL_PollEvent(&events);
	switch(events){
		...
	}
}

bool EventHandler::KeyDown(uint8_t i) const{
	return keys[i];
}

uint8_t State() const{
	return state;
}
