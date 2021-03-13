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

	Point start_position;
	Point position;
	Point position_offset;
	Point camera;
	Point camera_offset;
	bool is_moving = false;

	void move(Point player_movement);
};

#endif //RPG_TEST_PLAYER_HPP
