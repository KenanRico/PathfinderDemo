#ifndef CHARACTER_H
#define CHARACTER_H
//-------------------------------------
class Character{
	public:
		int row;
		int col;
	private:
		uint8_t render_entity_index;

	public:
		Character();
		~Character();
	private:
		Character(const Character&) = delete;
		Character& operator=(const Character&) = delete;

	public:
		void setRenderEntityIndex(uint8_t);
};
//-------------------------------------
#endif
