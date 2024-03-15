#include "definitions_include.h"

void character::set_move_left(const bool& left)
{
	move_left_ = left;
	if (left) {
		if (get_state() != character_action::IN_ROCKET)
			this->set_state(character_action::LOOK_LEFT);
		look_left_ = true;
		look_right_ = false;
		move_right_ = false;
		acceleration_x_ = 0;
	}

}
void character::set_move_right(const bool& right)
{
	move_right_ = right;

	if (right) {
		if (get_state() != character_action::IN_ROCKET)
			this->set_state(character_action::LOOK_RIGHT);
		look_left_ = false;
		look_right_ = true;
		move_left_ = false;
		acceleration_x_ = 0;
	}

}

void character::move_x(const float& left_bound, const float& right_bound)
{

	teleport_on_bounds(left_bound, right_bound);

	if (move_left_)
		translational::move({ move_x_ * -acceleration_x_ });
	else if (move_right_)
		translational::move({ move_x_ * acceleration_x_ });
	acceleration_x_ += 0.15f;

}
bool character::check_movement_direction(const game_object& plat, const bool& get_fake) {

	if (position_.y_ >= jump_beginning_ + jump_height_)
		set_move_down();
	else if (touches_other_objects_top(plat) && !get_fake) {
		if (position_.y_ <= jump_beginning_)
			set_move_up(jump_beginning_);
		else if (!move_up_ && position_.y_ > jump_beginning_)
		{
			set_move_up(plat.top());
			return true;
		}
	}
	return false;

}
void character::move_y(const float& elapsed_time)
{

	float delta_move = elapsed_time * move_y_ + acceleration_y_;

	translational::move({ 0, (move_up_ ? 1.f : -1.f) * delta_move });

	acceleration_y_ += 0.15f;


}

void character::stand()
{
	if (!move_up_ && look_left_ && get_state() != character_action::LOOK_LEFT)
		this->set_state(character_action::LOOK_LEFT);
	else if (!move_up_ && look_right_ && get_state() != character_action::LOOK_RIGHT)
		this->set_state(character_action::LOOK_RIGHT);
}

void character::sit()
{

	if (look_left_)
		this->set_state(character_action::LOOK_LEFT_AND_SIT);
	else if (look_right_)
		this->set_state(character_action::LOOK_RIGHT_AND_SIT);
}

void character::set_move_up(const float& position)
{
	move_up_ = true;
	acceleration_y_ = 0.f;
	jump_beginning_ = position;
	stand();
}

void character::set_move_down()
{
	move_up_ = false;
	acceleration_y_ = 0.f;
	sit();
}

character character::create_character(const string& txt_path, const translational& pos, const float& jump_height)
{
	float move_y = jump_height * 1.5f;
	float move_x = precision<float>(jump_height / 150.f, 1);


	character result{
		game_object::create_game_object(txt_path, pos),
		jump_height,
		pos.get_position().y_,
		move_y,
		move_x };

	return result;
}
