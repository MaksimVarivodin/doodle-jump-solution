#pragma once
#include "declarations.h"
#include "translational.h"
#include "point2d.h"
class camera : public translational
{
	
	point2d<float> scale_ = {};
	point2d<bool> axis_invertions_ = {};


	bool object_left_side_in_camera(const float & object_left, const float& object_width) const;
	bool object_right_side_in_camera( const float & object_right, const float& object_width) const;
	bool object_top_side_in_camera(const float & object_top) const;
	bool object_bottom_side_in_camera( const float & object_bottom, const float& object_height) const;
protected:
	point2d<float> offset_ = {};
	width_height camera_size_ = {};
public:
	
	camera(
		const translational& pos,
		const point2d<int>& size,
		const point2d<float>& scale,
		const point2d<bool>& invert)
		:translational::translational(pos),
		camera_size_(size),
		scale_(scale),
		axis_invertions_(invert),
		offset_({0, 0})
	{
	}
	camera(const camera& other)
		:translational::translational(other.get_position()),
		camera_size_(other.camera_size_),
		scale_(other.scale_),
		axis_invertions_(other.axis_invertions_),
		offset_(other.offset_)	
	{}
	camera() :translational::translational{}{}
	float left()	const	{ return this->get_position().x_ ; }
	float right()	const	{ return this->get_position().x_ + camera_size_.x_; }
	float top()		const	{ return this->get_position().y_ ; }
	float bottom()	const	{ return this->get_position().y_ + camera_size_.y_; }
	float center_x() const { return this->get_position().x_ + camera_size_.x_ / 2.f; }
	float center_y() const { return this->get_position().y_ + camera_size_.y_ / 2.f; }

	point2d<float> world_object_to_screen(const game_object& obj) const;
	point2d<float> world_object_to_screen(const point2d<float>& pos, const float& width, const float& height) const;
	point2d<float> screen_object_to_world(const game_object& obj) const;
	point2d<float> screen_object_to_world(const point2d<float>& pos) const;

	
	float get_world_bottom() const {
		return screen_object_to_world({0, bottom()}).y_;
	}

	bool object_in_camera(const point2d<float> & screen_coords, const float & width, const float& height) const;
	bool object_above_camera(const game_object& obj) ;
	bool object_under_camera(const game_object& obj) ;
	float object_above_camera_center(const float& screen_coords) const;
	float object_under_camera_bottom(const float& screen_coords) const;

	float follow(const game_object& world_obj);
	camera(camera&& other) = default;
	camera& operator= (const camera& other) = default;
	camera& operator= (camera&& other) = default;
	~camera() = default;
};

