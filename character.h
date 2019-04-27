#ifndef CHARACTER_H
#define CHARACTER_H
//-------------------------------------

#include "entity.h"

#include <stdint.h>

class Character{
	public:
		int row;
		int col;
		Entity* render_entity;
		uint64_t timer;
		int speed; //1~10

	public:
		Character();
		~Character();
	private:
		Character& operator=(const Character&) = delete;

	public:
		void SetRenderEntity(Entity* e);
};
//-------------------------------------
#endif
