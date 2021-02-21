#include "game.hpp"
#include "assets.hpp"
#include "player.hpp"
#include <cstring>
#include <memory>
#include <cstdlib>

using namespace blit;

constexpr uint16_t level_width = 64;
constexpr uint16_t level_height = 64;
constexpr uint32_t level_size = level_width * level_height;

uint8_t *layer_data[4];
TileMap *layers[4];
Player *player;

#pragma pack(push,1)
struct TMX {
	char head[4];
	uint8_t empty_tile;
	uint16_t width;
	uint16_t height;
	uint16_t layers;
	uint8_t data[];
};
#pragma pack(pop)

Mat3 camera;
std::function<Mat3(uint8_t)> level_line_interrupt_callback = [](uint8_t y) -> Mat3 {
	return camera;
};

void draw_background() {
	TMX *tmx = (TMX *)asset_map;

	if(tmx->width > level_width) return;
	if(tmx->height > level_height) return;

	for(auto i = 0u; i < tmx->layers; i++) {
		layer_data[i] = (uint8_t *)malloc(level_size);
		layers[i] = new TileMap((uint8_t *)layer_data[i], nullptr, Size(level_width, level_height), screen.sprites);

		// Load the level data from the map memory
		memset(layer_data[i], 0, level_size);

		for (auto x = 0u; x < tmx->width; x++) {
			for (auto y = 0u; y < tmx->height; y++) {
				auto src = y * tmx->width + x;
				auto dst = y * level_width + x;
				layer_data[i][dst] = tmx->data[src + i * level_size];
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////
//
// init()
//
// setup your game here
//
void init() {
	set_screen_mode(ScreenMode::lores);
	screen.sprites = Surface::load(asset_sprites);

	draw_background();

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
	// clear the screen -- screen is a reference to the frame buffer and can be used to draw all things with the 32blit
	screen.clear();

	for (auto & layer : layers) {
		layer->draw(&screen, Rect(0, 0, screen.bounds.w, screen.bounds.h), level_line_interrupt_callback);
	}

	player->draw();
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
