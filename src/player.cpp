//
// Created by daniel on 20.02.21.
//

#include <iostream>
#include "player.hpp"
#include "utils/utils.hpp"
#include "utils/layer_handler.hpp"

using namespace blit;

/*
 * Calculates camera position in scale 100x to prevent float rounding issues
 */
Player::Player() {
	Player::absolute_position = Point(0, 0);
	Player::camera = Point(absolute_position.x * 100, absolute_position.y * 100);
	Player::camera_offset = Point(0, 0);
}

void Player::move_up() {
	move(Point(0, -1));
}

void Player::move_down() {
	move(Point(0, 1));
}

void Player::move_left() {
	move(Point(-1, 0));
}

void Player::move_right() {
	move(Point(1, 0));
}

void Player::move(Point player_movement) {
	Point next_position = absolute_position + player_movement;
	if (!is_moving && LayerHandler::get_flag(next_position) == LayerHandler::SOLID) {
		//TODO rename camera_offset (name is required later for map border cam offset)
		//TODO rename to movement_offset and make movement Vector obsolete
		camera_offset = player_movement * 100;
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

Vec2 Player::update_camera() {
	if (!is_moving) {
		return world_to_screen(camera.x / 100.0f, camera.y / 100.0f);
	}

	if (camera.x < camera.x + camera_offset.x) {
		camera.x += velocity;
		camera_offset.x -= velocity;
	} else if (camera.x > camera.x + camera_offset.x) {
		camera.x -= velocity;
		camera_offset.x += velocity;
	} else if (camera.y < camera.y + camera_offset.y) {
		camera.y += velocity;
		camera_offset.y -= velocity;
	} else if (camera.y > camera.y + camera_offset.y) {
		camera.y -= velocity;
		camera_offset.y += velocity;
	} else {
		is_moving = false;
		camera_offset = Point(0, 0);
	}

	return world_to_screen(camera.x / 100.0f, camera.y / 100.0f);
}