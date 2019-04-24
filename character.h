#ifndef CHARACTER_H
#define CHARACTER_H
//-------------------------------------

#include "entity.h"

class Character{
	public:
		int row;
		int col;
		Entity* render_entity;

	public:
		Character(int, int);
		~Character();
	private:
		Character() = delete;
		Character& operator=(const Character&) = delete;

	public:
		void SetRenderEntity(Entity* e);
};
//-------------------------------------
#endif
