//
// Created by daniel on 27.02.21.
//

#include "32blit.hpp"

#ifndef RPG_TEST_UTILS_HPP
#define RPG_TEST_UTILS_HPP

using namespace blit;

constexpr uint8_t tile_size = 8;

namespace utils {
	Point tile(const Point &p);
	Point world_to_screen(const Point &p);
	Point screen_to_world(const Point &p);
}
#endif