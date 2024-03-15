#include "definitions_include.h"

#ifdef _CAMERA_DEBUG
	void game_view::draw_camera_frame() const
{
	this->view_frame_.draw(this->get_position());
}
#endif // 


void game_view::draw(const vector<game_object>& world_objects) const
{
	for (const auto& obj : world_objects)
		this->draw(obj);
	
}

void game_view::draw(const game_object& world_object) const
{
	point2d<float> in_cam_coords = this->world_object_to_screen(world_object);
	if (this->object_in_camera(in_cam_coords, world_object.width(), world_object.height()))
		world_object.draw(in_cam_coords);
}

game_view game_view::create_view(
#ifdef _CAMERA_DEBUG
	const drawable& frame,
#endif // 	
	const point2d<float>& pos,
	const width_height& size,
	const point2d<float>& scale,
	const point2d<bool>& axis_invert)
{
	return game_view(
#ifdef _CAMERA_DEBUG
		frame,
#endif // 
		{ pos },
		size,
		scale,
		axis_invert
	);
}
