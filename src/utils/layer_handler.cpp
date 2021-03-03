//
// Created by daniel on 28.02.21.
//

#include <cstring>
#include <iostream>
#include "assets.hpp"
#include "layer_handler.hpp"

constexpr uint16_t level_width = 64;
constexpr uint16_t level_height = 64;
constexpr uint32_t level_size = level_width * level_height;

#pragma pack(push,1)
struct TMX {
	char head[4];
	uint8_t empty_tile;
	uint16_t width;
	uint16_t height;
	uint8_t layers;
	uint8_t data[];
};
#pragma pack(pop)

LayerHandler::LayerHandler(std::function<Mat3(uint8_t)> *level_line_interrupt_callback) {
	LayerHandler::level_line_interrupt_callback = level_line_interrupt_callback;
}

void LayerHandler::generate_map() {
	TMX *tmx = (TMX *)asset_map;

	if(tmx->width > level_width) return;
	if(tmx->height > level_height) return;

	for(auto i = 0u; i < tmx->layers; i++) {
		layer_data[i] = (uint8_t *)malloc(level_size);
		layers[i] = new TileMap((uint8_t *)layer_data[i], nullptr, Size(level_width, level_height), screen.sprites);

		// Load the level data from the map memory
		memset(layer_data[i], 0, level_size);

		for (auto x = 0u; x < tmx->width; x++) {
			for (auto y = 0u; y < tmx->height; y++) {
				auto src = y * tmx->width + x;
				auto dst = y * level_width + x;
				layer_data[i][dst] = tmx->data[src + i * level_size];
			}
		}
	}

	//TODO remove; Letzte zeile wird an den anfang gehängt
//	for (auto y = 0u; y < tmx->height; y++) {
//		for (auto x = 0u; x < tmx->width; x++) {
//			std::cout << std::to_string(layers[0]->tile_at(Point(x, y))) + ", ";
//		}
//		std::cout << std::endl;
//	}
}

void LayerHandler::draw_map() {
	for (auto & layer : layers) {
		layer->draw(&screen, Rect(0, 0, screen.bounds.w, screen.bounds.h), *level_line_interrupt_callback);
	}
}

bool LayerHandler::has_flag(Point p, LayerHandler::TileFlags flag) {
	uint8_t i = layer_count;
	uint8_t j;
	uint8_t tile_id;
	bool flag_found = false;

	while(!flag_found && i > 0) {
		i--;
		j = 0;
		tile_id = layers[i]->tile_at(p);

		while(!flag_found && j < flags[flag].size()) {
			if (tile_id == flags[flag].at(j) - 1) {
				flag_found = true;
			}
			j++;
		}
	}

	return flag_found;
}

void LayerHandler::set_flags(LayerHandler::TileFlags flag, const std::vector<uint8_t> &tiles) {
	flags[flag] = tiles;
}
