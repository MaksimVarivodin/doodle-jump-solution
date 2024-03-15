#include "definitions_include.h"

bool camera::object_left_side_in_camera(const float& object_x, const float& object_width) const
{
	return this->left() - object_width / 4.f <= object_x;
}

bool camera::object_right_side_in_camera(const float& object_x, const float& object_width) const
{
	return this->right() + object_width / 4.f >= object_x;
}

bool camera::object_top_side_in_camera(const float& object_y) const
{
	return this->top() <= object_y;
}

bool camera::object_bottom_side_in_camera(const float& object_y, const float& object_height) const
{
	return this->bottom() >= object_y + object_height;
}

point2d<float> camera::world_object_to_screen(const game_object& obj) const
{
	return world_object_to_screen(obj.get_position(), (float)obj.width(), (float)obj.height());
}

point2d<float> camera::world_object_to_screen(const point2d<float>& pos, const float& width, const float& height) const
{
	float x_coord = pos.x_ + (axis_invertions_.x_ ? width : 0.f);
	float y_coord = pos.y_ + (axis_invertions_.y_ ? height : 0.f);

	// simplified transform without matrixes

	if (axis_invertions_.x_) {
		x_coord *= scale_.x_ * (-1.f);
		x_coord += get_position().x_ + camera_size_.x_ - offset_.x_;
	}
	if (axis_invertions_.y_) {
		y_coord *= scale_.y_ * (-1.f);
		y_coord += get_position().y_ + camera_size_.y_ - offset_.y_;
	}
	return point2d<float>{x_coord, y_coord};
}

point2d<float> camera::screen_object_to_world(const game_object& obj) const
{
	point2d<float> pos = screen_object_to_world(obj.get_position());
	pos.x_ -= (axis_invertions_.x_ ? obj.width() : 0.f);
	pos.y_ -= (axis_invertions_.y_ ? obj.height() : 0.f);
	return pos;
}

point2d<float> camera::screen_object_to_world(const point2d<float>& pos) const
{
	float x_coord = pos.x_;
	float y_coord = pos.y_;

	if (axis_invertions_.x_) {

		x_coord -= get_position().x_ + camera_size_.x_ - offset_.x_;
		x_coord /= scale_.x_ * (-1.f);
	}
	if (axis_invertions_.y_) {

		y_coord -= get_position().y_ + camera_size_.y_ - offset_.y_;
		y_coord /= scale_.y_ * (-1.f);
	}

	return point2d<float>(x_coord, y_coord);
}


bool camera::object_in_camera(const point2d<float>& screen_coords, const float& width, const float& height) const
{

	// checking if the "screened" object is in camera
#ifdef _CAMERA_DEBUG
	bool left_ok = object_left_side_in_camera(screen_coords.x_, width);
	bool right_ok = object_right_side_in_camera(screen_coords.x_, width);

	bool top_ok = object_top_side_in_camera(screen_coords.y_);
	bool bottom_ok = object_bottom_side_in_camera(screen_coords.y_, height);

	return left_ok && right_ok && top_ok && bottom_ok;
#endif //
#ifndef _CAMERA_DEBUG
	return object_left_side_in_camera(screen_coords.x_, width) &&
		object_right_side_in_camera(screen_coords.x_, width) &&
		object_top_side_in_camera(screen_coords.y_) &&
		object_bottom_side_in_camera(screen_coords.y_, height);
#endif // !_CAMERA_DEBUG



}

bool camera::object_above_camera(const game_object& obj)
{
	point2d<float> object_screen_position = world_object_to_screen(obj);
	float object_bottom = object_screen_position.y_ + obj.height();
	return object_bottom < this->top();
}
bool camera::object_under_camera(const game_object& obj)
{
	point2d<float> object_screen_position = world_object_to_screen(obj);
	float object_top = object_screen_position.y_;
	return object_top > this->bottom();
}

float camera::object_above_camera_center(const float& screen_coords) const
{
#ifdef _CONSOLE_DEBUG
	cout << "Camera center = " << center_y() << endl;
#endif // _CONSOLE_DEBUG
	return center_y() - screen_coords;
}

float camera::object_under_camera_bottom(const float& screen_coords) const
{
#ifdef _CONSOLE_DEBUG
	cout << "Camera bottom = " << bottom() << endl;
#endif // _CONSOLE_DEBUG
	return screen_coords - bottom();
}

float camera::follow(const game_object& world_obj)
{


	point2d<float> object_screen_coords = world_object_to_screen(world_obj);

#ifdef _CONSOLE_DEBUG
	cout << "\n\nScreen y_ = " << object_screen_coords.y_ << " Height = " << world_obj.height() << endl;
	cout << "Together = " << object_screen_coords.y_ + world_obj.height() << endl;
#endif // _CONSOLE_DEBUG
	float above = object_above_camera_center(object_screen_coords.y_);
	float under = object_under_camera_bottom(object_screen_coords.y_ + world_obj.height());

	if (above > 0.f) {
		offset_.y_ -= above;
		return above;
	}

	else if (under > 0.f) {
		offset_.y_ += under;
		return -under;
	}
	return 0.f;

#ifdef _CONSOLE_DEBUG
	cout << "above = " << above << endl;
	cout << "under = " << under << endl;
	cout << "\n\n\n";
#endif // _CONSOLE_DEBUG


}
