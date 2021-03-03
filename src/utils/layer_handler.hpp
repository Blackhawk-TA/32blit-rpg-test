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
		SOLID = 0,
		WATER = 1,
		WALL = 2
	};

	explicit LayerHandler(std::function<Mat3(uint8_t)> *level_line_interrupt_callback);
	void generate_map();
	void draw_map();
	void set_flags(LayerHandler::TileFlags flag, const std::vector<uint8_t> &tiles);
	bool has_flag(Point p, TileFlags flag);

private:
	constexpr static uint8_t layer_count = 4;
	std::function<Mat3(uint8_t)> *level_line_interrupt_callback;
	std::array<std::vector<uint8_t>, layer_count> flags;
	uint8_t *layer_data[layer_count]{};
	TileMap *layers[layer_count]{};
};

#endif //RPG_TEST_LAYER_HANDLER_HPP
