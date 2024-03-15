#pragma once
#include "declarations.h"
#include "game_environment.h"

class game_window : public Framework {

public:
	game_window(const int& size_x, const int& size_y)
		:size_x_(size_x), size_y_(size_y)
	{
	}
	game_environment game_env_;
	int mouse_x_ = 0;
	int mouse_y_ = 0;
	int size_x_ = 640;
	int size_y_ = 1024;
	bool fullscreen_enabled = false;
	bool right_key_released = true;
	bool left_key_released = true;


	virtual void PreInit(int& width, int& height, bool& fullscreen);
	

	virtual bool Init();

	virtual void Close();

	virtual bool Tick();

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative);

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased);

	virtual void onKeyPressed(FRKey k);

	virtual void onKeyReleased(FRKey k);

	virtual const char* GetTitle() override;
	
};
