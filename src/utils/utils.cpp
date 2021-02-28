//
// Created by daniel on 27.02.21.
//

#include "utils.hpp"

using namespace blit;

Point tile(const Point &p) {
	return Point(p.x / tile_size, p.y / tile_size);
}

Point world_to_screen(const Point &p) { //TODO implement
	return Point(
		0,
		0
	);
}

Point screen_to_world(const Point &p) { //TODO implement
	return Point(
		0,
		0
	);
}
