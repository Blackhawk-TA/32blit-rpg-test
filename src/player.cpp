//
// Created by daniel on 20.02.21.
//

#include "player.hpp"
#include "utils/layer_handler.hpp"
#include "utils/utils.hpp"

using namespace blit;

constexpr uint8_t tile_set_x_pos = 15;
constexpr uint8_t tile_set_y_pos = 8;
constexpr uint8_t player_width = 1;
constexpr uint8_t player_height = 1;

Player::Player() {
	Player::absolute_position = Point(1, 0);
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
	Point next_position = absolute_position + player_movement;
	//relative_position is relative use world_to_screen method
	if (LayerHandler::get_flag(next_position) == LayerHandler::SOLID) {
//		relative_position += movement; //TODO relative position komplett entfernen
		absolute_position += movement; //TODO absolute position darf nicht geändert werden weil es darauf basierend rendert, LSG: auf anderem wert rendern, am besten fall screen zentrum bzw neue variable mit camera position einführen
	}

	movement = Point(0, 0);
}

void Player::draw() {
	//TODO find better way to select sprite from tile set
	//TODO render sprite based on camera position (preferable in the middle) instead of using absolute_position
	screen.sprite(Rect(tile_set_x_pos, tile_set_y_pos, player_width, player_height), pixel(absolute_position)); //TODO change to middle of screen
}

Vec2 Player::update_camera() { //TODO rounding issue when moving
	if(camera.x < relative_position.x) { //TODO absolute position zu relativer durch berechnung machen, evtl movement benutzen
		camera.x += 0.1f;
	}
	if(camera.x > relative_position.x) {
		camera.x -= 0.1f;
	}
	if(camera.y < relative_position.y) {
		camera.y += 0.1f;
	}
	if(camera.y > relative_position.y) {
		camera.y -= 0.1f;
	}

	return Vec2(camera.x, camera.y);
}