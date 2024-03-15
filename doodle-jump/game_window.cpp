#include "definitions_include.h"

void game_window::PreInit(int& width, int& height, bool& fullscreen)
{
	width = size_x_;
	height = size_y_;
	fullscreen = fullscreen_enabled;
}

bool game_window::Init()
{
	game_env_.initialize(size_x_, size_y_, 250.f);
	return true;
}

void game_window::Close()
{
	game_env_.stop_threads();
}

bool game_window::Tick()
{
	game_env_.draw();
	game_env_.change_on_tick();
	return false;
}

void game_window::onMouseMove(int x, int y, int xrelative, int yrelative)
{
	mouse_x_ = x;
	mouse_y_ = y;
}

void game_window::onMouseButtonClick(FRMouseButton button, bool isReleased)
{
	if (button == FRMouseButton::LEFT && isReleased)
		game_env_.shoot({ mouse_x_, mouse_y_ });
	if(button== FRMouseButton::RIGHT && isReleased)
		game_env_.re_init();
}

void game_window::onKeyPressed(FRKey k)
{
	switch (k) {
	case FRKey::RIGHT:
		game_env_.move_right();
		break;
	case FRKey::LEFT:
		game_env_.move_left();
		break;
	}
}

void game_window::onKeyReleased(FRKey k)
{
	switch (k) {
	case FRKey::RIGHT:
		game_env_.move_right(false);
		break;
	case FRKey::LEFT:
		game_env_.move_left(false);
		break;
	}
}

const char* game_window::GetTitle()
{
	return "Arcanoid";
}
