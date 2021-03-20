//
// Created by daniel on 28.02.21.
//
#include "32blit.hpp"

#ifndef RPG_TEST_LAYER_HANDLER_HPP
#define RPG_TEST_LAYER_HANDLER_HPP

using namespace blit;

class LayerHandler { //TODO cleanup, check and understand pointer in function parameters

public:
	enum TileFlags {
		SOLID = 1,
		WATER = 2,
		WALL = 3,
		OBJECTS = 4
	};

	static void draw_map(std::function<Mat3(uint8_t)> *level_line_interrupt_callback);
	static void generate_map();
	static void set_flags(LayerHandler::TileFlags flag, const std::vector<uint8_t> &tiles);
	static uint8_t get_flag(Point &p);
};

#endif //RPG_TEST_LAYER_HANDLER_HPP
