//
// Created by daniel on 20.02.21.
//

#include "player.hpp"

using namespace blit;

constexpr Point size = Point(1, 1);
constexpr uint8_t tile_set_x_pos = 15;
constexpr uint8_t tile_set_y_pos = 8;
constexpr uint8_t player_width = 1;
constexpr uint8_t player_height = 1;

Player::Player(uint16_t screen_width, uint16_t screen_height) {
	Player::screen_location = Point(screen_width / 2, screen_height / 2);
	Player::screen_location += Point(1, 1);
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
	screen.sprite(Rect(tile_set_x_pos, tile_set_y_pos, player_width, player_height), screen_location);
}

Vec2 Player::update_camera() {
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