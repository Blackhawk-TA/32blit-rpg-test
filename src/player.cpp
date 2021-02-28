//
// Created by daniel on 20.02.21.
//

#include "player.hpp"

using namespace blit;

constexpr uint8_t tile_set_x_pos = 15;
constexpr uint8_t tile_set_y_pos = 8;
constexpr uint8_t player_width = 1;
constexpr uint8_t player_height = 1;

Player::Player() {
	Player::screen_location = Point(screen.bounds.w / 2, screen.bounds.h / 2 - tile_size / 2);
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
	//TODO check if player can move
	position += player_movement;
	movement = Point(0, 0);
}

void Player::draw() {
	//TODO find better way to select sprite from tile set
	screen.sprite(Rect(tile_set_x_pos, tile_set_y_pos, player_width, player_height), screen_location);
}

Vec2 Player::update_camera() { //TODO rounding issue when moving
	if(camera.x < position.x) {
		camera.x += 0.1f;
	}
	if(camera.x > position.x) {
		camera.x -= 0.1f;
	}
	if(camera.y < position.y) {
		camera.y += 0.1f;
	}
	if(camera.y > position.y) {
		camera.y -= 0.1f;
	}

	return Vec2(camera.x, camera.y);
}