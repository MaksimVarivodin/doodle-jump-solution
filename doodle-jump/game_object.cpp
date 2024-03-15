#include "definitions_include.h"


game_object game_object::create_game_object(const string&  txt_path, const translational& pos)
{
	return game_object(states::create_states( txt_path), pos);
}

game_object game_object::create_game_object(const string& txt_path, const int& st, const translational& pos)
{
	return game_object(states::create_states( txt_path, st), pos);
}

void game_object::draw() const
{
	this->states::draw(this->position_);
}

void game_object::draw(const point2d<float>& pos) const
{
	this->states::draw(pos);
}

bool game_object::touches_other_objects_left(const game_object& other) const
{
	return this->right() == other.left() && this->right() <= other.right() && this->bottom() >= other.bottom() && this->top() <= other.top();
}

bool game_object::touches_other_objects_right(const game_object& other) const
{
	return this->left() == other.right() && this->left() >= other.left() && this->bottom() >= other.bottom() && this->top() <= other.top();
}

bool game_object::touches_other_objects_top(const game_object& other) const
{
	float offset_for_legs = width()/3.f;
	bool legs_step_on_plat_left =  this->right() >= (other.left()+ offset_for_legs);
	bool legs_step_on_plat_right =  this->left () <= (other.right()- offset_for_legs);
	return this->bottom() <= other.top() && this->top() >= other.top() && legs_step_on_plat_left &&legs_step_on_plat_right;
}

bool game_object::touches_other_objects_bottom(const game_object& other) const
{
	return this->top() >= other.bottom() && this->bottom() <= other.bottom() && this->right() >= (other.left() + width()/6.f) && this-> left () <= (other.right()- width()/6.f);
}

bool game_object::touches(const game_object& other) const
{
	return	touches_other_objects_left(other)	||
			touches_other_objects_right(other)	||
			touches_other_objects_top(other)	||
			touches_other_objects_bottom(other);
}

void game_object::set_translational(const translational& other)
{
	this->position_ = other.get_position();
}

float game_object::left() const
{
	float pos = this->get_position().x_;
	return pos;
}

float game_object::right() const
{

	float pos = this->get_position().x_ + width();
	return pos;
}

float game_object::top() const
{
	float pos = this->get_position().y_+ height();
	return pos;
}

float game_object::bottom() const
{
	float pos = this->get_position().y_ ;
	return pos;
}

game_object game_object::create_game_object(const vector<string>& path, const translational& pos)
{
	return game_object(states::create_states( path), pos);
}

