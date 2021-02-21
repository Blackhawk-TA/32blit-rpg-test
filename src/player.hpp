//
// Created by daniel on 20.02.21.
//

#include "32blit.hpp"

#ifndef RPG_TEST_PLAYER_HPP
#define RPG_TEST_PLAYER_HPP

using namespace blit;

class Player {
public:
	explicit Player(uint16_t screen_width, uint16_t screen_height);
	void draw();
	void move_up();
	void move_down();
	void move_left();
	void move_right();
	Vec2 update_camera();

private:
	Point start_position;
	Point position; //The position on the grid
	Point movement;
	Point screen_location; //The location in pixel
	Vec2 camera;

	void move(Point player_movement);
};


#endif //RPG_TEST_PLAYER_HPP
