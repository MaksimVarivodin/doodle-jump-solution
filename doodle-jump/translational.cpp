#include "definitions_include.h"

void translational::teleport_on_bounds(const float& left_bound, const float& right_bound)
{
	if (this->position_.x_ >= right_bound)
		this->set_position(point2d<>{left_bound, this->position_.y_ });
	else if (this->position_.x_ < left_bound)
		this->set_position(point2d<>{right_bound, this->position_.y_ });
}

void translational::move(const point2d<float>& delta)
{
	position_ += delta;
}

