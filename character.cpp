#include "character.h"


Character::Character(int r, int c): row(r), col(c), render_entity_index(0){

}

Character::~Character(){


}

void Character::setRenderEntityIndex(uint8_t i){
	render_entity_index = i;
}
