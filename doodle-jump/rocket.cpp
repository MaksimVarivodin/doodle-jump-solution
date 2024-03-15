#include "definitions_include.h"
void rocket::set_under_ability(character& doodle_)
{
	doodle_state_ = doodle_.get_state();
	doodle_.set_state(character_action::IN_ROCKET);
}

void rocket::set_ability_finished(character& doodle_, const platform& plat)
{
	doodle_.set_state(doodle_state_);
	doodle_.move_up_ = true;
	doodle_.acceleration_y_ = 0.f;
	doodle_.jump_beginning_ = plat.top();
	ability_lasts_ = 0.f;
}
void rocket::move_doodle_x(character& doodle_, const float& left_bound, const float& right_bound)
{
	doodle_.teleport_on_bounds(left_bound, right_bound);
	if (doodle_.move_left_)
		doodle_.translational::move({ doodle_.move_x_ * -doodle_.acceleration_x_ });
	else if (doodle_.move_right_)
		doodle_.translational::move({ doodle_.move_x_ * doodle_.acceleration_x_ });
	doodle_.acceleration_x_ += 0.15f;

}

void rocket::move_doodle_y(character& doodle_, const float& elapsed_time)
{
	ability_lasts_ += elapsed_time;
	doodle_.translational::move({0, elapsed_time * jetpack_move_y_});
}

rocket rocket::create_rocket(const translational& pos, const float& jetpack_move_y)
{
	return rocket(game_object::create_game_object(R"(\sprites_data\rocket.txt)", pos), jetpack_move_y);
}
