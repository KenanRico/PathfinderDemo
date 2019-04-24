#include "character.h"

#include "entity.h"


Character::Character(int r, int c): row(r), col(c), render_entity(nullptr){

}

Character::~Character(){


}

void Character::SetRenderEntity(Entity* e){
	render_entity = e;
}
