#pragma once
#include "declarations.h"
#include "camera.h"

class game_view : public camera
{

#ifdef _CAMERA_DEBUG
	drawable view_frame_;
#endif // _CONSOLE_DEBUG


public:
#ifdef _CAMERA_DEBUG
	void draw_camera_frame() const;
#endif // 
	void draw(const vector<game_object>& world_objects) const;
	void draw(const game_object& world_object) const;

	game_view(
#ifdef _CAMERA_DEBUG
		const drawable& view_frame,
#endif // _CONSOLE_DEBUG

		const translational& pos,
		const point2d<int>& size,
		const point2d<float>& scale,
		const point2d<bool>& invert)
		:camera::camera(pos, size, scale, invert)

#ifdef _CAMERA_DEBUG
		,view_frame_(view_frame)
#endif // 
	{
	}
	static game_view create_view(
#ifdef _CAMERA_DEBUG
		const drawable& frame,
#endif // _CONSOLE_DEBUG
		const point2d<float>& pos,
		const width_height& size,
		const point2d<float>& scale,
		const point2d<bool>& axis_invert
	);
	game_view(const game_view& other)
		:camera::camera(other) {}
	game_view() : camera::camera() {}

	game_view(game_view&& other) = default;
	game_view& operator= (const game_view& other) = default;
	game_view& operator= (game_view&& other) = default;
	~game_view() = default;
};

