//
// Created by daniel on 20.02.21.
//

#include "utils/utils.hpp"

#ifndef RPG_TEST_PLAYER_HPP
#define RPG_TEST_PLAYER_HPP

using namespace blit;

class Player {
public:
	explicit Player();
	void draw();
	void move_up();
	void move_down();
	void move_left();
	void move_right();
	Vec2 update_camera();

private:
	const Point size = Point(1, 1);
	const Point tile = Point(15, 8);
	const uint8_t velocity = 5;

	Vec2 camera_offset;
	Point absolute_position; //The absolut position of the player on the grid
	Vec2 camera;
	bool is_moving = false;

	void move(Vec2 player_movement);
};

#endif //RPG_TEST_PLAYER_HPP
