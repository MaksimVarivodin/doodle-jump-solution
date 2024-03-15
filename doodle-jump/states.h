#pragma once
#include "declarations.h"

class states
{
protected:
	vector<drawable> pictures_;
	int current_state_ = 0; 
public:
	bool is_state_ok() const{return pictures_.size() > 0 && current_state_ >= 0 && current_state_ < pictures_.size();}
	bool is_state_ok(const int& new_st) const { return pictures_.size() > 0 && new_st >= 0 && new_st < pictures_.size();}
	void set_state(const int& st){ if(is_state_ok(st))	current_state_ = st;}
	int get_state() const {return current_state_;}
	drawable get_drawable(const int& st) const;

	void draw(const translational& pos) const;
	void draw_state(const point2d<float>& pos, const int & skin_index_) const;
	int width() const;
	int height() const;
	void scale(const float & scale_x, const float & scale_y);
	void set_size(const int & width, const int& height);

	static states create_states(const vector<string>& paths);
	static states create_states(const string& txt_file);
	static states create_states(const string& txt_file, const int& st);

	states(const vector<drawable>& skins, const int& st)
		: pictures_(skins), current_state_(st)
	{
	}
	states(const vector<drawable>& skins):
		states(skins, 0)
	{}
	states(const states & st)
		:pictures_(st.pictures_), current_state_(st.current_state_)
	{}
	states() : states(vector<drawable>(), character_action::DEFAULT)
	{}
	~states()
	{
		pictures_.clear();
	}
};

