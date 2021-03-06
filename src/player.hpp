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
	const float velocity = 0.05f;

	Point camera_offset; //The position on the grid relative to the starting position
	Point absolute_position; //The absolut position on the grid
	Point movement;
	Vec2 camera;

	void move(Point player_movement);
};

#endif //RPG_TEST_PLAYER_HPP
