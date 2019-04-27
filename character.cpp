#include "character.h"

#include "entity.h"

Character::Character(): row(0), col(0), render_entity(nullptr), timer(0), speed(0){

}

Character::~Character(){

}

void Character::SetRenderEntity(Entity* e){
	render_entity = e;
	render_entity->Enable();
}
