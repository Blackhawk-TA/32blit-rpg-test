//
// Created by daniel on 27.02.21.
//

#include "utils.hpp"

using namespace blit;

Point screen_to_world(const Point &p) {
	return Point(p.x / tile_size, p.y / tile_size);
}

Vec2 screen_to_world(const Vec2 &p) {
	return Vec2(p.x / tile_size, p.y / tile_size);
}

Point world_to_screen(const Point &p) {
	return Point(p.x * tile_size, p.y * tile_size);
}

Vec2 world_to_screen(const Vec2 &p) {
	return Vec2(p.x * tile_size, p.y * tile_size);
}

Vec2 world_to_screen(const float &x, const float &y) {
	return Vec2(x * tile_size, y * tile_size);
}
