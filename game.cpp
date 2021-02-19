#include <cstring>
#include <memory>
#include <cstdlib>
#include "game.hpp"

using namespace blit;

constexpr uint16_t screen_width = 160;
constexpr uint16_t screen_height = 120;

constexpr uint16_t level_width = 64;
constexpr uint16_t level_height = 64;

uint8_t *level_data;
TileMap* level;

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
///////////////////////////////////////////////////////////////////////////
//
// init()
//
// setup your game here
//
void init() {
	set_screen_mode(ScreenMode::hires); //lores is zoomed
	screen.sprites = SpriteSheet::load(asset_objects);

	level_data = (uint8_t *)malloc(level_width * level_height);
	level = new TileMap((uint8_t *)level_data, nullptr, Size(level_width, level_height), screen.sprites);

	TMX *tmx = (TMX *)asset_map;

	if(tmx->width > level_width) return;
	if(tmx->height > level_height) return;

	// Load the level data from the map memory
	memset(level_data, 0, level_width * level_height);

	for(auto x = 0u; x < tmx->width; x++) {
		for(auto y = 0u; y < tmx->height; y++) {
			auto src = y * tmx->width + x;
			auto dst = y * level_width + x;
			level_data[dst] = tmx->data[src];
		}
	}
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

	level->draw(&screen, Rect(0, 0, screen.bounds.w, screen.bounds.h), level_line_interrupt_callback);
}

///////////////////////////////////////////////////////////////////////////
//
// update(time)
//
// This is called to update your game state. time is the
// amount if milliseconds elapsed since the start of your game
//
void update_camera(uint32_t time) {
	camera = Mat3::identity();
//	camera *= Mat3::translation(Vec2(0, 0)); // offset to middle of world
//	camera *= Mat3::translation(Vec2(-screen_width / 2, -screen_height / 2)); // transform to centre of framebuffer
}
void update(uint32_t time) {
	update_camera(time);
}
