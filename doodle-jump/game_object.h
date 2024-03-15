#pragma once
#include "declarations.h"
#include "states.h"
class game_object: public states, public translational
{
public:

	void draw () const;
	void draw(const point2d<float>& pos) const;
	bool touches_other_objects_left(const game_object& other) const;
	bool touches_other_objects_right(const game_object& other) const;
	bool touches_other_objects_top(const game_object& other) const;
	bool touches_other_objects_bottom(const game_object& other) const;
	bool touches(const game_object& other) const;

	void set_translational(const translational& other);
	translational get_translational() const {return {this->get_position()};}
	states get_skins() const {return states{this->states::pictures_, this->states::current_state_};}
	float left() const;
	float right() const;
	float top() const;
	float bottom() const;
	static game_object create_game_object(const vector<string> & path, const translational& pos);
	static game_object create_game_object(const string & txt_path, const translational& pos);
	static game_object create_game_object(const string & txt_path, const int & st, const translational& pos);
	game_object(const states& st, const translational& pos)
		: states::states(st), translational::translational(pos)
	{}
	game_object(const game_object& obj)
		: game_object(states(obj.pictures_, obj.current_state_),translational(obj.position_) )
	{}
	game_object():game_object(states{}, translational{}){}

	~game_object()
	{
		states::~states();
	}
};

