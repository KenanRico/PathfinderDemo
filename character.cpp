#include "character.h"

#include "entity.h"


Character::Character(int r, int c): row(r), col(c), render_entity(nullptr), timer(0), speed(6){

}

Character::~Character(){


}

void Character::SetRenderEntity(Entity* e){
	render_entity = e;
}
