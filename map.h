#ifndef MAP_H
#define MAP_H
//-----------------------------------
class Map{
	private:
		std::vector<float> mapping;
		uint16_t rows;
		uint16_t cols;
		uint8_t render_path_index;
		uint8_t render_wall_index;
	public:
		Map(const char*);
		~Map();
	private:
		Map() = delete;
		Map(const Map&) = delete;
		Map& operator=(const Map&) = delete;
	public:
		void SetRenderIndices(uint8_t, uint8_t);
};
//-----------------------------------
#endif
