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
	move(Vec2(0, -1));
}

void Player::move_down() {
	move(Vec2(0, 1));
}

void Player::move_left() {
	move(Vec2(-1, 0));
}

void Player::move_right() {
	move(Vec2(1, 0));
}

void Player::move(Vec2 player_movement) {
	Point next_position = absolute_position + player_movement;
	if (!is_moving && LayerHandler::get_flag(next_position) == LayerHandler::SOLID) {
		//TODO rename camera_offset (name is required later for map border cam offset)
		//TODO rename to movement_offset and make movement Vector obsolete
		camera_offset = player_movement;
		absolute_position = next_position;
		is_moving = true;
	}
}

void Player::draw() {
	screen.sprite(
		Rect(tile.x, tile.y, size.x, size.y),
		Point(screen.bounds.w / 2.0f, screen.bounds.h / 2.0f)
	);
}

Vec2 Player::update_camera() { //TODO set camera and its offset scale to 100 within the entire class and only convert on return
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