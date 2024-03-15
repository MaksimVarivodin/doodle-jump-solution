#pragma once
#include "declarations.h"
#include "game_object.h"
#include "character.h"
class rocket: public game_object
{
	float jetpack_move_y_;
	int doodle_state_ = 0;
	float ability_lasts_ = 0;
public:

	bool ability_finished() const {return ability_lasts_ >= 10.f;}
	void set_under_ability(character& doodle_);
	void set_ability_finished(character& doodle_, const platform& );

	void move_doodle_x(character& doodle_, const float& left_bound,	const float & right_bound);
	void move_doodle_y(character& doodle_, const float& elapsed_time);
	static rocket create_rocket(const translational& pos, const float & jetpack_move_y);

	rocket(const game_object& obj, const float & jetpack_move_y)
	:	game_object::game_object(obj), jetpack_move_y_(jetpack_move_y)
	{

	}
	rocket(): game_object::game_object(), jetpack_move_y_(0.f)
	{}
};

