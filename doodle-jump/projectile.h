#pragma once
#include "declarations.h"
#include "game_object.h"
class projectile : public game_object
{
	float move_speed_;
	point2d<float> direction_;
public:

	static projectile create_projectile(const translational & pos, const float& speed,
		point2d<float>direction);

	void set_move_direction(const point2d<float>& direction){direction_ = direction; }
	void set_move_speed(const float & speed){move_speed_ = speed;}

	void move(const float& left_bound, const float& right_bound);

	projectile(const game_object& obj,
		const float& speed,
		point2d<float>direction)
	:game_object::game_object(obj),
		move_speed_(speed),
		direction_(direction)
	{}
	projectile()
	:game_object::game_object{},
		move_speed_(0),
		direction_{}
	{}

};

