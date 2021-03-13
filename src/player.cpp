//
// Created by daniel on 20.02.21.
//

#include <iostream>
#include "player.hpp"
#include "utils/utils.hpp"
#include "utils/layer_handler.hpp"

using namespace blit;

constexpr uint8_t camera_scale = 100;
constexpr float camera_scale_float = 100.0f;

/*
 * Calculates camera position in scale 100x to prevent float rounding issues
 */
Player::Player() {
	Player::start_position = Point(10, 10); //TODO calc camera for init position
	Player::position = start_position;
	Player::position_offset = Point(0, 0);
	Player::camera = screen_to_world(Vec2(-screen.bounds.w / 2.0f, -screen.bounds.h / 2.0f)) * camera_scale + (start_position * camera_scale);
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
	Point next_position = position + player_movement;
	if (!is_moving /*&& LayerHandler::get_flag(next_position) == LayerHandler::SOLID*/) {
		camera_offset = player_movement * camera_scale;
		position = next_position;
		is_moving = true;
	}
}

void Player::draw() {
	screen.sprite(
		Rect(tile.x, tile.y, size.x, size.y),
		Point(screen.bounds.w / 2.0f, screen.bounds.h / 2.0f) + world_to_screen(position_offset) / camera_scale_float
	);
}

Vec2 Player::update_camera() {
	if (!is_moving) {
		return world_to_screen(camera.x / camera_scale_float, camera.y / camera_scale_float);
	}

	//TODO remove magic numbers + fix camera cutting off the top of the screen and some of the bottom
	if (camera_offset.x != 0) { //Movement along the x axis
		if (position_offset.x == 0 && camera.x + camera_offset.x >= 0 && camera.x + camera_offset.x <= (level_width - 20) * camera_scale) { //TODO find out where the 20 comes from
			if (camera.x < camera.x + camera_offset.x) {
				camera.x += velocity;
				camera_offset.x -= velocity;
			} else if (camera.x > camera.x + camera_offset.x) {
				camera.x -= velocity;
				camera_offset.x += velocity;
			}
		} else { // Move the player when the camera is at the map border
			if (camera_offset.x > 0) {
				position_offset.x += velocity;
				camera_offset.x -= velocity;
			} else if (camera_offset.x < 0) {
				position_offset.x -= velocity;
				camera_offset.x += velocity;
			}
		}
	} else if (camera_offset.y != 0) { //Movement along the y axis
		if (position_offset.y == 0 && camera.y + camera_offset.y >= 0 && camera.y + camera_offset.y <= (level_height - 15) * camera_scale) { //TODO find out where the 15 comes from
			if (camera.y < camera.y + camera_offset.y) {
				camera.y += velocity;
				camera_offset.y -= velocity;
			} else if (camera.y > camera.y + camera_offset.y) {
				camera.y -= velocity;
				camera_offset.y += velocity;
			}
		} else { // Move the player when the camera is at the map border
			if (camera_offset.y > 0) {
				position_offset.y += velocity;
				camera_offset.y -= velocity;
			} else if (camera_offset.y < 0) {
				position_offset.y -= velocity;
				camera_offset.y += velocity;
			}
		}
	} else {
		is_moving = false;
	}

	return world_to_screen(camera.x / camera_scale_float, camera.y / camera_scale_float);
}