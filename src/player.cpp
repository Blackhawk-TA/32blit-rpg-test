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
	Player::camera_offset = Player::camera;
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
	if (LayerHandler::get_flag(next_position) == LayerHandler::SOLID) {
		camera_offset += movement;
		absolute_position = next_position;
	}

	movement = Point(0, 0);
}

void Player::draw() {
	screen.sprite(
		Rect(tile.x, tile.y, size.x, size.y),
		Point(screen.bounds.w / 2.0f, screen.bounds.h / 2.0f)
	);
}

Vec2 Player::update_camera() { //TODO rounding issue when moving, see TODO.txt in documents folder
	if(camera.x < camera_offset.x) {
		camera.x += velocity;
	}
	if(camera.x > camera_offset.x) {
		camera.x -= velocity;
	}
	if(camera.y < camera_offset.y) {
		camera.y += velocity;
	}
	if(camera.y > camera_offset.y) {
		camera.y -= velocity;
	}

	return world_to_screen(camera.x, camera.y);
}