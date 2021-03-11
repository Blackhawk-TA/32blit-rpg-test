//
// Created by daniel on 20.02.21.
//

#include "player.hpp"
#include "utils/utils.hpp"
#include "utils/layer_handler.hpp"

using namespace blit;

Player::Player() {
	Player::absolute_position = Point(0, 0);
	Player::camera = Vec2(absolute_position.x, absolute_position.y);
	Player::camera_offset = Vec2(0, 0);
}

void Player::move_up() {
	movement.y = -1;
	move(movement);
}

void Player::move_down() {
	movement.y = 1;
	move(movement);
}

void Player::move_left() {
	movement.x = -1;
	move(movement);
}

void Player::move_right() {
	movement.x = 1;
	move(movement);
}

void Player::move(Point player_movement) {
	Point next_position = absolute_position + player_movement;
	if (!is_moving && LayerHandler::get_flag(next_position) == LayerHandler::SOLID) {
		camera_offset = movement; //TODO movement and offset are equal currently
		absolute_position = next_position;
		is_moving = true;
	}

	movement = Vec2(0, 0);
}

void Player::draw() {
	screen.sprite(
		Rect(tile.x, tile.y, size.x, size.y),
		Point(screen.bounds.w / 2.0f, screen.bounds.h / 2.0f)
	);
}

Vec2 Player::update_camera() {
	if (!is_moving) {
		return world_to_screen(camera.x, camera.y);
	}

	//TODO dont declare vars in update function
	bool moved = false;
	uint16_t x = camera.x * 100;
	uint16_t y = camera.y * 100; //TODO rounding issue causes overflow
	int8_t o_x = camera_offset.x * 100;
	int8_t o_y = camera_offset.y * 100;

	if (camera.x < camera.x + camera_offset.x) {
		x += velocity;
		o_x -= velocity;
		moved = true;
	}
	if (!moved && camera.x > camera.x + camera_offset.x) {
		x -= velocity;
		o_x += velocity;
		moved = true;
	}
	if (!moved && camera.y < camera.y + camera_offset.y) {
		y += velocity;
		o_y -= velocity;
		moved = true;
	}
	if (!moved && camera.y > camera.y + camera_offset.y) {
		y -= velocity;
		o_y += velocity;
		moved = true;
	}

	if (!moved) {
		is_moving = false;
		camera_offset = Vec2(0, 0);
	}

	camera.x = x / 100.0f; //TODO optimize by using multiplication if it does not cause rounding issues
	camera.y = y / 100.0f;
	camera_offset.x = o_x / 100.0f;
	camera_offset.y = o_y / 100.0f;

	return world_to_screen(camera.x, camera.y);
}