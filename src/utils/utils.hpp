//
// Created by daniel on 27.02.21.
//

#include "32blit.hpp"

#ifndef RPG_TEST_UTILS_HPP
#define RPG_TEST_UTILS_HPP

using namespace blit;

constexpr uint8_t tile_size = 8;

Point screen_to_world(const Point &p);
Vec2 screen_to_world(const Vec2 &p);

Point world_to_screen(const Point &p);
Vec2 world_to_screen(const Vec2 &p);
Vec2 world_to_screen(const float &x, const float &y);

#endif