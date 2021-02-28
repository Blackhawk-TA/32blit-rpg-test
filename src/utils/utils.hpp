//
// Created by daniel on 27.02.21.
//

#include "32blit.hpp"

using namespace blit;

constexpr uint8_t tile_size = 8;

Point tile(const Point &p);
Point world_to_screen(const Point &p);
Point screen_to_world(const Point &p);
