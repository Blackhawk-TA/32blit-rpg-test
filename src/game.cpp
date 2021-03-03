#include "game.hpp"
#include "assets.hpp"
#include "player.hpp"
#include "utils/layer_handler.hpp"

using namespace blit;

LayerHandler *layer_handler;
Player *player;

Mat3 camera;
std::function<Mat3(uint8_t)> level_line_interrupt_callback = [](uint8_t y) -> Mat3 {
	return camera;
};

///////////////////////////////////////////////////////////////////////////
//
// init()
//
// setup your game here
//
void init() {
	set_screen_mode(ScreenMode::lores);
	screen.sprites = Surface::load(asset_sprites);

	LayerHandler::generate_map();

	LayerHandler::set_flags(LayerHandler::SOLID, {65, 66, 67, 68, 69, 81, 82, 83, 84, 85, 97, 98, 99, 100, 101, 2, 3, 4, 5, 6, 7, 20});
	LayerHandler::set_flags(LayerHandler::WATER, {32, 113, 114, 115, 116, 117});
	LayerHandler::set_flags(LayerHandler::WALL, {21, 22, 23});

	player = new Player();
}

///////////////////////////////////////////////////////////////////////////
//
// render(time)
//
// This function is called to perform rendering of the game. time is the
// amount if milliseconds elapsed since the start of your game
//
void render(uint32_t time) {
	float ms_start = now();

	// clear the screen -- screen is a reference to the frame buffer and can be used to draw all things with the 32blit
	screen.clear();

	LayerHandler::draw_map(&level_line_interrupt_callback);
	player->draw();

	//Draw fps meter
	float ms_end = now();
	screen.alpha = 255;
	screen.pen = Pen(255, 255, 255, 100);
	screen.rectangle(Rect(1, 120 - 10, 20, 9));
	screen.pen = Pen(255, 255, 255, 200);
	std::string fms = std::to_string((int)(1/((ms_end - ms_start)/1000)));
	screen.text(fms, minimal_font, Rect(3, 120 - 9, 10, 16));

	int block_size = 4;
	for (uint32_t i = 0; i < (ms_end - ms_start); i++) {
		screen.pen = Pen(i * 5, 255 - (i * 5), 0);
		screen.rectangle(Rect(i * (block_size + 1) + 1 + 21, screen.bounds.h - block_size - 1, block_size, block_size));
	}
}

void update_camera(uint32_t time) {
	camera = Mat3::identity();

	Vec2 player_camera = player->update_camera();
	camera *= Mat3::translation(Vec2(player_camera.x * 8.0f, player_camera.y * 8.0f));
}

///////////////////////////////////////////////////////////////////////////
//
// update(time)
//
// This is called to update your game state. time is the
// amount if milliseconds elapsed since the start of your game
//
void update(uint32_t time) {
	static uint32_t last_buttons = 0;
	static uint32_t changed = 0;
	changed = buttons ^ last_buttons;

	if (buttons & changed & Button::DPAD_UP) {
		player->move_up();
	}
	if (buttons & changed & Button::DPAD_DOWN) {
		player->move_down();
	}
	if (buttons & changed & Button::DPAD_LEFT) {
		player->move_left();
	}
	if (buttons & changed & Button::DPAD_RIGHT) {
		player->move_right();
	}

	last_buttons = buttons;

	update_camera(time);
}
