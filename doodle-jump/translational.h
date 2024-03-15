#pragma once
#include "declarations.h"

/// <summary>
/// Class translational stores a position of an object.
/// Provides methods to modify this position.
/// </summary>

class translational
{
protected:
	point2d<float> position_{};
public:	

	translational(const point2d<float>& position_)
		: position_(position_)
	{
	}
	translational(const translational& pos)
		: position_(pos.position_)
	{}
	translational():translational(point2d<float>{}){}

	void teleport_on_bounds(const float& left_bound, const float& right_bound);

	void move(const point2d<float>& delta);
	void set_position(const point2d<float>& position_in){ 
		position_ = position_in;
	}
	void get_position(point2d<float>& position_out) const{ 
		position_out = position_;
	}
	const point2d<float> &get_position() const{ return position_; }
};

