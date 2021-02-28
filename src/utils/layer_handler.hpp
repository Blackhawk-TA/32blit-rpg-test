//
// Created by daniel on 28.02.21.
//

#pragma once

#include "32blit.hpp"

#ifndef RPG_TEST_LAYER_HANDLER_HPP
#define RPG_TEST_LAYER_HANDLER_HPP

using namespace blit;

class LayerHandler { //TODO cleanup, check and understand pointer in function parameters
public:
	enum TileFlags {
		SOLID = 1,
		WATER = 2,
		WALL = 3
	};

	explicit LayerHandler(std::function<Mat3(uint8_t)> *level_line_interrupt_callback);
	void generate_map();
	void draw_map();
	void add_flags(uint8_t tiles[], TileFlags flag);
	bool has_flag(Point p, TileFlags flag);

private:
	std::function<Mat3(uint8_t)> *level_line_interrupt_callback;
};

#endif //RPG_TEST_LAYER_HANDLER_HPP
